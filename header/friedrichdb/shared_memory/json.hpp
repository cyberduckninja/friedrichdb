#include <boost/interprocess/containers/map.hpp>
#include <boost/interprocess/containers/vector.hpp>
#include <boost/interprocess/containers/string.hpp>
#include <boost/interprocess/smart_ptr/unique_ptr.hpp>


#include <boost/interprocess/allocators/allocator.hpp>
#include <boost/interprocess/sync/interprocess_sharable_mutex.hpp>
#include <boost/interprocess/managed_shared_memory.hpp>
#include <boost/core/demangle.hpp>

#include <boost/multi_index_container.hpp>

#include <boost/chrono.hpp>
#include <boost/config.hpp>
#include <boost/throw_exception.hpp>

#include <array>
#include <atomic>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <typeindex>
#include <typeinfo>

#include "node_allocator.hpp"


namespace bip = boost::interprocess;
using boost::interprocess::managed_unique_ptr;
using boost::interprocess::make_managed_unique_ptr;



using segment = bip::managed_shared_memory;
using manager = typename segment::segment_manager;

template<typename T>
using allocator = bip::allocator<T, manager>;

template<typename T>
using node_allocator = chainbase::node_allocator<T, manager>;

template <class Key, class T>
using map_shared = boost::interprocess::map<Key,T,std::less<Key>,allocator<T>>;

template <class T>
using vector_shared = boost::interprocess::vector<T,allocator<T>>;

using string_shared = boost::interprocess::basic_string<char,std::char_traits<char>,allocator<char>>;

template <typename K, typename V, typename KH = std::hash<K>, typename KEq = std::equal_to<K> >
using unordered_map_shared = std::unordered_map<K, V, KH, KEq, allocator<std::pair<const K, V>> >;

template<typename K>
using unique_ptr_shared = managed_unique_ptr<K,manager>;

template<class T>
using make_managed_unique_ptr = make_managed_unique_ptr<T,manager>;


enum class type : int  {
    null_type = 0x00,
    boolean_type,
    number_type,
    string_type,
    array_type,
    object_type,
    int64_type
};

enum { INDENT_WIDTH = 2 };

struct null final {};

template<class T>
class incomplete_wrapper final {
public:

    incomplete_wrapper() = default;

    incomplete_wrapper(const incomplete_wrapper&) {}

    incomplete_wrapper& operator=(const incomplete_wrapper&) {
        return *this;
    }

    T& get() {
        return *data_;
    }

    const T& get() const {
        return *data_;
    }

    template<class... Args>
    void set(Args&&... args) {
        data_ = make_managed_unique_ptr<T>(std::forward<Args>(args)...);
    }


private:
    unique_ptr_shared<T> data_;
};

class value final {
public:
    using array =  vector_shared<value>;
    using object = map_shared<string_shared, value> ;

    union _storage {
        bool boolean_;
        double number_;
        int64_t int64_;
        incomplete_wrapper<string_shared>string_;
        incomplete_wrapper<array> array_;
        incomplete_wrapper<object>object_;
    };

    int type_;
    incomplete_wrapper<_storage> u_;

public:
    value();
    value(int type, bool);
    explicit value(bool b);
    explicit value(int64_t i);
    explicit value(double n);
    explicit value(const std::string &s);
    explicit value(const array &a);
    explicit value(const object &o);
#if PICOJSON_USE_RVALUE_REFERENCE
    explicit value(std::string &&s);
  explicit value(array &&a);
  explicit value(object &&o);
#endif
    explicit value(const char *s);
    value(const char *s, size_t len);
    ~value();
    value(const value &x);
    value &operator=(const value &x);
#if PICOJSON_USE_RVALUE_REFERENCE
    value(value &&x) PICOJSON_NOEXCEPT;
  value &operator=(value &&x) PICOJSON_NOEXCEPT;
#endif
    void swap(value &x) noexcept ;
    template <typename T> bool is() const;
    template <typename T> const T &get() const;
    template <typename T> T &get();
    template <typename T> void set(const T &);
#if PICOJSON_USE_RVALUE_REFERENCE
    template <typename T> void set(T &&);
#endif
    bool evaluate_as_boolean() const;
    const value &get(const size_t idx) const;
    const value &get(const std::string &key) const;
    value &get(const size_t idx);
    value &get(const std::string &key);

    bool contains(const size_t idx) const;
    bool contains(const std::string &key) const;
    std::string to_str() const;
    template <typename Iter> void serialize(Iter os, bool prettify = false) const;
    std::string serialize(bool prettify = false) const;

private:
    template <typename T> value(const T *); // intentionally defined to block implicit conversion of pointer to bool
    template <typename Iter> static void _indent(Iter os, int indent);
    template <typename Iter> void _serialize(Iter os, int indent) const;
    std::string _serialize(int indent) const;
    void clear();
};

typedef value::array array;
typedef value::object object;

inline value::value() : type_(null_type), u_() {
}

inline value::value(int type, bool) : type_(type), u_() {
    switch (type) {
#define INIT(p, v)                                                                                                                 \
  case p##type:                                                                                                                    \
    u_.p = v;                                                                                                                      \
    break
        INIT(boolean_, false);
        INIT(number_, 0.0);
#ifdef PICOJSON_USE_INT64
        INIT(int64_, 0);
#endif
        INIT(string_, new std::string());
        INIT(array_, new array());
        INIT(object_, new object());
#undef INIT
        default:
            break;
    }
}

inline value::value(bool b) : type_(type::boolean_type), u_() {
    u_.boolean_ = b;
}

#ifdef PICOJSON_USE_INT64
inline value::value(int64_t i) : type_(int64_type), u_() {
  u_.int64_ = i;
}
#endif

inline value::value(double n) : type_(type::number_type), u_() {
    if (
#ifdef _MSC_VER
!_finite(n)
#elif __cplusplus >= 201103L
std::isnan(n) || std::isinf(n)
#else
        isnan(n) || isinf(n)
#endif
            ) {
        throw std::overflow_error("");
    }
    u_.number_ = n;
}

inline value::value(const std::string &s) : type_(type::string_type), u_() {
    u_.string_ = new std::string(s);
}

inline value::value(const array &a) : type_(type::array_type), u_() {
    u_.array_ = new array(a);
}

inline value::value(const object &o) : type_(type::object_type), u_() {
    u_.object_ = new object(o);
}

#if PICOJSON_USE_RVALUE_REFERENCE
inline value::value(std::string &&s) : type_(string_type), u_() {
  u_.string_ = new std::string(std::move(s));
}

inline value::value(array &&a) : type_(array_type), u_() {
  u_.array_ = new array(std::move(a));
}

inline value::value(object &&o) : type_(object_type), u_() {
  u_.object_ = new object(std::move(o));
}
#endif

inline value::value(const char *s) : type_(type::string_type), u_() {
    u_.string_ = new std::string(s);
}

inline value::value(const char *s, size_t len) : type_(type::string_type), u_() {
    u_.string_ = new std::string(s, len);
}

inline void value::clear() {
    switch (type_) {
#define DEINIT(p)                                                                                                                  \
  case p##type:                                                                                                                    \
    delete u_.p;                                                                                                                   \
    break
        DEINIT(string_);
        DEINIT(array_);
        DEINIT(object_);
#undef DEINIT
        default:
            break;
    }
}

inline value::~value() {
    clear();
}

inline value::value(const value &x) : type_(x.type_), u_() {
    switch (type_) {
#define INIT(p, v)                                                                                                                 \
  case p##type:                                                                                                                    \
    u_.p = v;                                                                                                                      \
    break
        INIT(string_, new string_shared(*x.u_.string_));
        INIT(array_, new array(*x.u_.array_));
        INIT(object_, new object(*x.u_.object_));
#undef INIT
        default:
            u_ = x.u_;
            break;
    }
}

inline value &value::operator=(const value &x) {
    if (this != &x) {
        value t(x);
        swap(t);
    }
    return *this;
}

#if PICOJSON_USE_RVALUE_REFERENCE
inline value::value(value &&x) PICOJSON_NOEXCEPT : type_(null_type), u_() {
  swap(x);
}
inline value &value::operator=(value &&x) PICOJSON_NOEXCEPT {
  swap(x);
  return *this;
}
#endif
inline void value::swap(value &x) noexcept {
std::swap(type_, x.type_);
std::swap(u_, x.u_);
}

#define IS(ctype, jtype)                                                                                                           \
  template <> inline bool value::is<ctype>() const {                                                                               \
    return type_ == jtype##_type;                                                                                                  \
  }
IS(null, null)
IS(bool, boolean)
#ifdef PICOJSON_USE_INT64
IS(int64_t, int64)
#endif
IS(std::string, string)
IS(array, array)
IS(object, object)
#undef IS
template <> inline bool value::is<double>() const {
    return type_ == number_type
#ifdef PICOJSON_USE_INT64
        || type_ == int64_type
#endif
            ;
}

#define GET(ctype, var)                                                                                                            \
  template <> inline const ctype &value::get<ctype>() const {                                                                      \
    PICOJSON_ASSERT("type mismatch! call is<type>() before get<type>()" && is<ctype>());                                           \
    return var;                                                                                                                    \
  }                                                                                                                                \
  template <> inline ctype &value::get<ctype>() {                                                                                  \
    PICOJSON_ASSERT("type mismatch! call is<type>() before get<type>()" && is<ctype>());                                           \
    return var;                                                                                                                    \
  }
GET(bool, u_.boolean_)
GET(std::string, *u_.string_)
GET(array, *u_.array_)
GET(object, *u_.object_)
#ifdef PICOJSON_USE_INT64
GET(double,
    (type_ == int64_type && (const_cast<value *>(this)->type_ = number_type, const_cast<value *>(this)->u_.number_ = u_.int64_),
     u_.number_))
GET(int64_t, u_.int64_)
#else
GET(double, u_.number_)
#endif
#undef GET

#define SET(ctype, jtype, setter)                                                                                                  \
  template <> inline void value::set<ctype>(const ctype &_val) {                                                                   \
    clear();                                                                                                                       \
    type_ = jtype##_type;                                                                                                          \
    setter                                                                                                                         \
  }
SET(bool, boolean, u_.boolean_ = _val;)
SET(std::string, string, u_.string_ = new std::string(_val);)
SET(array, array, u_.array_ = new array(_val);)
SET(object, object, u_.object_ = new object(_val);)
SET(double, number, u_.number_ = _val;)
#ifdef PICOJSON_USE_INT64
SET(int64_t, int64, u_.int64_ = _val;)
#endif
#undef SET

#if PICOJSON_USE_RVALUE_REFERENCE
#define MOVESET(ctype, jtype, setter)                                                                                              \
  template <> inline void value::set<ctype>(ctype && _val) {                                                                       \
    clear();                                                                                                                       \
    type_ = jtype##_type;                                                                                                          \
    setter                                                                                                                         \
  }
MOVESET(std::string, string, u_.string_ = new std::string(std::move(_val));)
MOVESET(array, array, u_.array_ = new array(std::move(_val));)
MOVESET(object, object, u_.object_ = new object(std::move(_val));)
#undef MOVESET
#endif

inline bool value::evaluate_as_boolean() const {
    switch (type_) {
        case null_type:
            return false;
        case boolean_type:
            return u_.boolean_;
        case number_type:
            return u_.number_ != 0;
#ifdef PICOJSON_USE_INT64
        case int64_type:
    return u_.int64_ != 0;
#endif
        case string_type:
            return !u_.string_->empty();
        default:
            return true;
    }
}

inline const value &value::get(const size_t idx) const {
    static value s_null;
    PICOJSON_ASSERT(is<array>());
    return idx < u_.array_->size() ? (*u_.array_)[idx] : s_null;
}

inline value &value::get(const size_t idx) {
    static value s_null;
    PICOJSON_ASSERT(is<array>());
    return idx < u_.array_->size() ? (*u_.array_)[idx] : s_null;
}

inline const value &value::get(const std::string &key) const {
    static value s_null;
    PICOJSON_ASSERT(is<object>());
    object::const_iterator i = u_.object_->find(key);
    return i != u_.object_->end() ? i->second : s_null;
}

inline value &value::get(const std::string &key) {
    static value s_null;
    PICOJSON_ASSERT(is<object>());
    object::iterator i = u_.object_->find(key);
    return i != u_.object_->end() ? i->second : s_null;
}

inline bool value::contains(const size_t idx) const {
    PICOJSON_ASSERT(is<array>());
    return idx < u_.array_->size();
}

inline bool value::contains(const std::string &key) const {
    PICOJSON_ASSERT(is<object>());
    object::const_iterator i = u_.object_->find(key);
    return i != u_.object_->end();
}

inline std::string value::to_str() const {
    switch (type_) {
        case null_type:
            return "null";
        case boolean_type:
            return u_.boolean_ ? "true" : "false";
#ifdef PICOJSON_USE_INT64
        case int64_type: {
    char buf[sizeof("-9223372036854775808")];
    SNPRINTF(buf, sizeof(buf), "%" PRId64, u_.int64_);
    return buf;
  }
#endif
        case number_type: {
            char buf[256];
            double tmp;
            SNPRINTF(buf, sizeof(buf), fabs(u_.number_) < (1ULL << 53) && modf(u_.number_, &tmp) == 0 ? "%.f" : "%.17g", u_.number_);
#if PICOJSON_USE_LOCALE
            char *decimal_point = localeconv()->decimal_point;
    if (strcmp(decimal_point, ".") != 0) {
      size_t decimal_point_len = strlen(decimal_point);
      for (char *p = buf; *p != '\0'; ++p) {
        if (strncmp(p, decimal_point, decimal_point_len) == 0) {
          return std::string(buf, p) + "." + (p + decimal_point_len);
        }
      }
    }
#endif
            return buf;
        }
        case string_type:
            return *u_.string_;
        case array_type:
            return "array";
        case object_type:
            return "object";
        default:
            PICOJSON_ASSERT(0);
#ifdef _MSC_VER
            __assume(0);
#endif
    }
    return std::string();
}

template <typename Iter> void copy(const std::string &s, Iter oi) {
    std::copy(s.begin(), s.end(), oi);
}

template <typename Iter>
struct serialize_str_char {
    Iter oi;
    void operator()(char c) {
        switch (c) {
#define MAP(val, sym)                                                                                                              \
  case val:                                                                                                                        \
    copy(sym, oi);                                                                                                                 \
    break
            MAP('"', "\\\"");
            MAP('\\', "\\\\");
            MAP('/', "\\/");
            MAP('\b', "\\b");
            MAP('\f', "\\f");
            MAP('\n', "\\n");
            MAP('\r', "\\r");
            MAP('\t', "\\t");
#undef MAP
            default:
                if (static_cast<unsigned char>(c) < 0x20 || c == 0x7f) {
                    char buf[7];
                    SNPRINTF(buf, sizeof(buf), "\\u%04x", c & 0xff);
                    copy(buf, buf + 6, oi);
                } else {
                    *oi++ = c;
                }
                break;
        }
    }
};

template <typename Iter> void serialize_str(const std::string &s, Iter oi) {
    *oi++ = '"';
    serialize_str_char<Iter> process_char = {oi};
    std::for_each(s.begin(), s.end(), process_char);
    *oi++ = '"';
}

template <typename Iter> void value::serialize(Iter oi, bool prettify) const {
    return _serialize(oi, prettify ? 0 : -1);
}

inline std::string value::serialize(bool prettify) const {
    return _serialize(prettify ? 0 : -1);
}

template <typename Iter> void value::_indent(Iter oi, int indent) {
    *oi++ = '\n';
    for (int i = 0; i < indent * INDENT_WIDTH; ++i) {
        *oi++ = ' ';
    }
}

template <typename Iter> void value::_serialize(Iter oi, int indent) const {
    switch (type_) {
        case string_type:
            serialize_str(*u_.string_, oi);
            break;
        case array_type: {
            *oi++ = '[';
            if (indent != -1) {
                ++indent;
            }
            for (array::const_iterator i = u_.array_->begin(); i != u_.array_->end(); ++i) {
                if (i != u_.array_->begin()) {
                    *oi++ = ',';
                }
                if (indent != -1) {
                    _indent(oi, indent);
                }
                i->_serialize(oi, indent);
            }
            if (indent != -1) {
                --indent;
                if (!u_.array_->empty()) {
                    _indent(oi, indent);
                }
            }
            *oi++ = ']';
            break;
        }
        case object_type: {
            *oi++ = '{';
            if (indent != -1) {
                ++indent;
            }
            for (object::const_iterator i = u_.object_->begin(); i != u_.object_->end(); ++i) {
                if (i != u_.object_->begin()) {
                    *oi++ = ',';
                }
                if (indent != -1) {
                    _indent(oi, indent);
                }
                serialize_str(i->first, oi);
                *oi++ = ':';
                if (indent != -1) {
                    *oi++ = ' ';
                }
                i->second._serialize(oi, indent);
            }
            if (indent != -1) {
                --indent;
                if (!u_.object_->empty()) {
                    _indent(oi, indent);
                }
            }
            *oi++ = '}';
            break;
        }
        default:
            copy(to_str(), oi);
            break;
    }
    if (indent == 0) {
        *oi++ = '\n';
    }
}

inline std::string value::_serialize(int indent) const {
    std::string s;
    _serialize(std::back_inserter(s), indent);
    return s;
}


template <typename T> struct last_error_t { static std::string s; };
template <typename T> std::string last_error_t<T>::s;


inline bool operator==(const value &x, const value &y) {
    if (x.is<null>())
        return y.is<null>();
#define PICOJSON_CMP(type)                                                                                                         \
  if (x.is<type>())                                                                                                                \
  return y.is<type>() && x.get<type>() == y.get<type>()
    PICOJSON_CMP(bool);
    PICOJSON_CMP(double);
    PICOJSON_CMP(std::string);
    PICOJSON_CMP(array);
    PICOJSON_CMP(object);
#undef PICOJSON_CMP
    assert(0);
#ifdef _MSC_VER
    __assume(0);
#endif
    return false;
}

inline bool operator!=(const value &x, const value &y) {
    return !(x == y);
}


namespace std {
    template <> inline void swap(picojson::value &x, picojson::value &y) {
        x.swap(y);
    }
}
