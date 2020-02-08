#pragma once

#include <cassert>
#include <boost/make_unique.hpp>
#include <boost/interprocess/containers/map.hpp>
#include <boost/interprocess/containers/vector.hpp>
#include <boost/interprocess/containers/string.hpp>
#include <boost/interprocess/smart_ptr/unique_ptr.hpp>

/// TODO:  decimal
class number_t final {
private:
    enum class type : std::uint8_t {
        uint8,
        uint16,
        uint32,
        uint64,
        int8,
        int16,
        int32,
        int64,
        float32,
        float64,
    };

    union payload {
        explicit payload(std::uint8_t value):uint8(value) {}
        explicit payload(std::uint16_t value):uint16(value) {}
        explicit payload(std::uint32_t value):uint32(value) {}
        explicit payload(std::uint64_t value):uint64(value) {}
        explicit payload(std::int8_t value):int8(value) {}
        explicit payload(std::int16_t value):int16(value) {}
        explicit payload(std::int32_t value):int32(value) {}
        explicit payload(std::int64_t value):int64(value) {}
        explicit payload(float value):float32(value) {}
        explicit payload(double value):float64(value) {}
        std::uint8_t  uint8;
        std::uint16_t uint16;
        std::uint32_t uint32;
        std::uint64_t uint64;
        std::int8_t   int8;
        std::int16_t  int16;
        std::int32_t  int32;
        std::int64_t  int64;
        float         float32;
        double        float64;
    };


public:
    number_t() = default;
    number_t(const number_t&) = delete;
    number_t&operator=(const number_t&) = delete;
    explicit number_t(std::uint8_t value):type_(type::uint8),payload_(value) {}
    explicit number_t(std::uint16_t value):type_(type::uint16),payload_(value) {}
    explicit number_t(std::uint32_t value):type_(type::uint32),payload_(value) {}
    explicit number_t(std::uint64_t value):type_(type::uint64),payload_(value) {}
    explicit number_t(std::int8_t value):type_(type::int8),payload_(value) {}
    explicit number_t(std::int16_t value):type_(type::int16),payload_(value) {}
    explicit number_t(std::int32_t value):type_(type::int32),payload_(value) {}
    explicit number_t(std::int64_t value):type_(type::int64),payload_(value) {}
    explicit number_t(float value):type_(type::float32),payload_(value) {}
    explicit number_t(double value):type_(type::float64),payload_(value) {}

    bool operator < (const number_t & rhs) const {

        switch (type_){
            case type::uint8:   return payload_.uint8   < rhs.payload_.uint8;
            case type::uint16:  return payload_.uint16  < rhs.payload_.uint32;
            case type::uint32:  return payload_.uint32  < rhs.payload_.uint32;
            case type::uint64:  return payload_.uint64  < rhs.payload_.uint64;
            case type::int8:    return payload_.int8    < rhs.payload_.int8;
            case type::int16:   return payload_.int16   < rhs.payload_.int16;
            case type::int32:   return payload_.int32   < rhs.payload_.int32;
            case type::int64:   return payload_.int64   < rhs.payload_.int64;
            case type::float32: return payload_.float32 < rhs.payload_.float32;
            case type::float64: return payload_.float64 < rhs.payload_.float64;
        }

    }

    bool operator> (const number_t & rhs) const{
        return rhs < *this;
    }

    bool operator<= (const number_t & rhs) const{

        switch (type_){
            case type::uint8:   return payload_.uint8   <= rhs.payload_.uint8;
            case type::uint16:  return payload_.uint16  <= rhs.payload_.uint32;
            case type::uint32:  return payload_.uint32  <= rhs.payload_.uint32;
            case type::uint64:  return payload_.uint64  <= rhs.payload_.uint64;
            case type::int8:    return payload_.int8    <= rhs.payload_.int8;
            case type::int16:   return payload_.int16   <= rhs.payload_.int16;
            case type::int32:   return payload_.int32   <= rhs.payload_.int32;
            case type::int64:   return payload_.int64   <= rhs.payload_.int64;
            case type::float32: return payload_.float32 <= rhs.payload_.float32;
            case type::float64: return payload_.float64 <= rhs.payload_.float64;
        }

    }

    bool operator>= (const number_t & rhs) const{
        return rhs <= *this;
    }

    bool operator == (const number_t & rhs) const {

        switch (type_){
            case type::uint8:   return payload_.uint8   == rhs.payload_.uint8;
            case type::uint16:  return payload_.uint16  == rhs.payload_.uint32;
            case type::uint32:  return payload_.uint32  == rhs.payload_.uint32;
            case type::uint64:  return payload_.uint64  == rhs.payload_.uint64;
            case type::int8:    return payload_.int8    == rhs.payload_.int8;
            case type::int16:   return payload_.int16   == rhs.payload_.int16;
            case type::int32:   return payload_.int32   == rhs.payload_.int32;
            case type::int64:   return payload_.int64   == rhs.payload_.int64;
            case type::float32: return payload_.float32 == rhs.payload_.float32;
            case type::float64: return payload_.float64 == rhs.payload_.float64;
        }

    }

    bool operator!= (const number_t & rhs) const{
        return !(*this == rhs);
    }

private:
    type type_;
    payload payload_;
};


class field_base final {
public:

    template <typename T>
    using AllocatorType = std::allocator<T>;
    using allocator_type = AllocatorType<field_base>;
    using pointer = typename std::allocator_traits<allocator_type>::pointer;
    using const_pointer = typename std::allocator_traits<allocator_type>::const_pointer;

    struct tensor_base final {
        boost::container::vector<unsigned int> shape_;
        boost::container::vector<field_base> base_;
    };

    using string_t = boost::container::string;
    using array_t =  boost::container::vector<field_base,AllocatorType<field_base>>;
    using object_t = boost::container::map<string_t,field_base, std::less<>,AllocatorType<std::pair<const string_t,field_base>>>;
    using boolean_t = bool;
    using tensor_t = tensor_base;

    enum class field_type : uint8_t {
        null,
        boolean,
        number,
        string,
        array,
        object
    };

    using key_type = string_t;
    using mapped_type = field_base;
    using reference = field_base&;
    using const_reference = const field_base&;
    using size_type = std::size_t ;
    using difference_type = std::ptrdiff_t;

public:
    field_base(const field_base&) = delete;
    field_base&operator=(const field_base&) = delete;

    ~field_base()  {
        assert_invariant();
        payload_->destroy(type_);
        payload_.reset();
    }


    field_base(const field_type v): type_(v), payload_(new payload(v)){
        assert_invariant();
    }


    field_base(std::nullptr_t = nullptr) : field_base(field_type::null){
        assert_invariant();
    }

    field_base(field_base&& other)  : type_(std::move(other.type_)),payload_(std::move(other.payload_)) {
        other.payload_.reset(new payload(field_type::number));
        other.assert_invariant();
        other.type_ = field_type::null;
        other.payload_.reset(new payload(field_type::null));
        assert_invariant();
    }

    field_base(bool value): type_(field_type::boolean), payload_(new payload(value)){}

    template <class T,  typename = typename std::enable_if<std::is_arithmetic<T>::value>::type>
    field_base(T value): type_(field_type::number), payload_(new payload(value)){}

    field_base(const string_t & value): type_(field_type::string), payload_(new payload(value)){}

    field_base(const char* value): type_(field_type::string), payload_(new payload(value)){}

    bool is_string() const noexcept {
        return type_ == field_type::string;
    }

    bool is_number() const noexcept {
        return type_ == field_type::number;
    }

    bool is_bool() const noexcept {
        return type_ == field_type::boolean;
    }

    bool is_array() const noexcept {
        return type_ == field_type::array;
    }

    bool is_object() const noexcept {
        return type_ == field_type::object;
    }

    bool is_null() const noexcept {
        return type_ == field_type::null;
    }

    const mapped_type& at(const key_type& k) const {
        return get_object().at(k);
    }

    template<class... Args>
    void emplace(Args&& ... args){

        assert((is_null() or is_object()));

        if (is_null()) {
            type_ = field_type::object;
            payload_.reset(new payload(field_type::object)) ;
            assert_invariant();
        }


        get_object().emplace(std::forward<Args>(args)...);

    }

    const_reference at (size_type n) const {
        return get_array().at(n);
    }

    template<class... Args>
    void emplace_back(Args&& ... args){

        assert (is_null() or is_array());

        if (is_null()){
            type_ = field_type::array;
            payload_.reset(new payload(field_type::array)) ;
            assert_invariant();
        }

        get_array().emplace_back(std::forward<Args>(args)...);

    }


    void erase(const typename object_t::key_type& key){
        get_object().erase(key);
    }
/*
    void erase(const size_type index){
        get_array().erase((get_array().begin() + static_cast<difference_type>(index)));
    }
*/

    bool empty() const noexcept {
        switch (type_) {
            case field_type::null: {
                return true;
            }

            case field_type::array: {
                return get_array().empty();
            }

            case field_type::object: {
                return get_object().empty();
            }

            default: {
                return false;
            }
        }
    }

    size_type size() const noexcept {
        switch (type_) {
            case field_type::null: {
                return 0;
            }

            case field_type::array: {
                return get_array().size();
            }

            case field_type::object: {
                return get_object().size();
            }

            default: {
                return 1;
            }
        }
    }

    void clear() noexcept {
        switch (type_) {

            case field_type::number: {
                ///get_number() = 0.0;
                break;
            }

            case field_type::boolean: {
                get_bool() = false;
                break;
            }

            case field_type::string: {
               get_string().clear();
                break;
            }

            case field_type::array: {
                get_array().clear();
                break;
            }

            case field_type::object: {
                get_object().clear();
                break;
            }

            default:
                break;
        }
    }

    bool operator< (const field_base & rhs) const {

        switch (type_){
            case field_type::null:   return false;
            case field_type::number: return get_number() < rhs.get_number();
            case field_type::string: return get_string() < rhs.get_string();
            case field_type::boolean:   return get_bool()   < rhs.get_bool();

        }

    }

    bool operator> (const field_base & rhs) const {
        return rhs < *this;
    }

    bool operator<= (const field_base & rhs) const {

        switch (type_){
            case field_type::null:   return true;
            case field_type::number: return get_number() <= rhs.get_number();
            case field_type::string: return get_string() <= rhs.get_string();
            case field_type::boolean:   return get_bool()   <= rhs.get_bool();
        }

    }

    bool operator>= (const field_base & rhs) const{
        return rhs <= *this;
    }

    bool operator == (const field_base & rhs) const {
        if (type_ != rhs.type_)
            return false;

        switch (type_){
            case field_type::null:   return true;
            case field_type::number: return get_number() == rhs.get_number();
            case field_type::string: return get_string() == rhs.get_string();
            case field_type::boolean:   return get_bool()   == rhs.get_bool();
        }

    }

    bool operator!= (const field_base & rhs) const{
        return !(*this == rhs);
    }


private:

    template<
            typename T,
            typename... Args
    >
    static T* create(Args&& ... args){
        AllocatorType<T> alloc;
        using AllocatorTraits = std::allocator_traits<AllocatorType<T>>;

        auto deleter = [&](T * object){
            AllocatorTraits::deallocate(alloc, object, 1);
        };
        std::unique_ptr<T, decltype(deleter)> object_tmp(AllocatorTraits::allocate(alloc, 1), deleter);
        AllocatorTraits::construct(alloc, object_tmp.get(), std::forward<Args>(args)...);
        assert(object_tmp != nullptr);
        return object_tmp.release();
    }

    union payload {

        object_t* object_;
        array_t*  array_;
        string_t* string_;
        boolean_t boolean_;
        number_t* number_;

        payload() = default;

        payload(boolean_t value)  : boolean_(value) {

        }

        template<class T, typename = typename std::enable_if<std::is_arithmetic<T>::value>::type>
        payload(T value)  : number_(create<number_t>(value)) {}

        payload(field_type t) {
            switch (t) {
                case field_type::object: {
                    object_ = create<object_t>();
                    break;
                }

                case field_type::array: {
                    array_ = create<array_t>();
                    break;
                }

                case field_type::string: {
                    string_ = create<string_t>();
                    break;
                }

                case field_type::boolean: {
                    boolean_ = boolean_t();
                    break;
                }

                case field_type::number: {
                    number_ = create<number_t>(0);
                    break;
                }

                case field_type::null: {
                    object_ = nullptr;  // silence warning, see #821
                    break;
                }

                default: {
                    object_ = nullptr;
                    assert(t == field_type::null);
                    break;
                }
            }
        }

        payload(const char* value) {
            string_ = create<string_t>(value);
        }

        payload(const string_t &value) {
            string_ = create<string_t>(value);
        }

        payload(string_t &&value) {
            string_ = create<string_t>(std::move(value));
        }

        payload(object_t &&value) {
            object_ = create<object_t>(std::move(value));
        }

        payload(array_t &&value) {
            array_ = create<array_t>(std::move(value));
        }

        void destroy(field_type t) noexcept {
            std::vector<field_base> stack;

            if (t == field_type::array) {
                stack.reserve(array_->size());
                std::move(array_->begin(), array_->end(), std::back_inserter(stack));
            } else if (t == field_type::object) {
                stack.reserve(object_->size());
                for (auto &&it : *object_) {
                    stack.push_back(std::move(it.second));
                }
            }

            while (not stack.empty()) {
                field_base current_item(std::move(stack.back()));
                stack.pop_back();

                if (current_item.is_array()) {
                    std::move(current_item.payload_->array_->begin(), current_item.payload_->array_->end(),
                              std::back_inserter(stack));
                    current_item.payload_->array_->clear();
                } else if (current_item.is_object()) {
                    for (auto &&it : *current_item.payload_->object_) {
                        stack.push_back(std::move(it.second));
                    }

                    current_item.payload_->object_->clear();
                }

            }

            switch (t) {
                case field_type::object: {
                    AllocatorType<object_t> alloc;
                    std::allocator_traits<decltype(alloc)>::destroy(alloc, object_);
                    std::allocator_traits<decltype(alloc)>::deallocate(alloc, object_, 1);
                    break;
                }

                case field_type::array: {
                    AllocatorType<array_t> alloc;
                    std::allocator_traits<decltype(alloc)>::destroy(alloc, array_);
                    std::allocator_traits<decltype(alloc)>::deallocate(alloc, array_, 1);
                    break;
                }

                case field_type::string: {
                    AllocatorType<string_t> alloc;
                    std::allocator_traits<decltype(alloc)>::destroy(alloc, string_);
                    std::allocator_traits<decltype(alloc)>::deallocate(alloc, string_, 1);
                    break;
                }

                case field_type::number: {
                    AllocatorType<string_t> alloc;
                    std::allocator_traits<decltype(alloc)>::destroy(alloc, number_);
                    ///std::allocator_traits<decltype(alloc)>::deallocate(alloc, number_, 1);
                    break;
                }

                default: {
                    break;
                }
            }
        }
    };

    void assert_invariant() const noexcept {
        assert(type_ != field_type::object or payload_->object_ != nullptr);
        assert(type_ != field_type::array or payload_->array_ != nullptr);
        assert(type_ != field_type::string or payload_->string_ != nullptr);
        assert(type_ != field_type::number or payload_->number_ != nullptr);
    }

    number_t & get_number() const {
        assert(type_ == field_type::number);
        return *(payload_->number_);
    }

    number_t & get_number() {
        assert(type_ == field_type::number);
        return *(payload_->number_);
    }

    bool get_bool() const {
        assert(type_ == field_type::boolean);
        return payload_->boolean_;
    }

    bool& get_bool()  {
        assert(type_ == field_type::boolean);
        return payload_->boolean_;
    }

    string_t & get_string() const {
        assert(type_ == field_type::string);
        return *(payload_->string_);
    }

    string_t & get_string(){
        assert(type_ == field_type::string);
        return *(payload_->string_);
    }

    object_t & get_object(){
        assert(type_ == field_type::object);
        return *(payload_->object_);
    }

    object_t &get_object() const {
        assert(type_ == field_type::object);
        return *(payload_->object_);
    }

    array_t & get_array(){
        assert(type_ == field_type::array);
        return *(payload_->array_);
    }

    array_t & get_array() const {
        assert(type_ == field_type::array);
        return *(payload_->array_);
    }

    field_type type_;
    boost::interprocess::unique_ptr<payload> payload_;

};