#ifndef FIELD_T_HPP
#define FIELD_T_HPP

#include "friedrichdb/data_types/ordering.h"
#include <vector>
#include <map>
#include <friedrichdb/data_types/type.hpp>

namespace friedrichdb {
#define DBMS_MIN_FIELD_SIZE 32
    constexpr static const int MIN_NON_POD = 16;

    /// Type tag.
    enum class types {
        null = 0,
        uint64 = 1,
        int64 = 2,
        float64 = 3,
        uint128 = 4,

        /// Non-POD types.

        string = 16,
        array = 17,
        object = 18,
    };


    const char *to_string(types which) {
        switch (which) {
            case types::null:
                return "Null";
            case types::uint64:
                return "uint64";
            case types::uint128:
                return "UInt128";
            case types::int64:
                return "Int64";
            case types::float64:
                return "float64";
            case types::string:
                return "string";
            case types::array:
                return "array";
            case types::object:
                return "object";

            default:
                throw std::exception("Bad type of Field");
        }
    }

    class field;

    using array = std::vector<field>;
    using object = std::map<string, field>

    template<typename F, typename Field>
    /// Field template parameter may be const or non-const Field.
    void dispatch(F &&f, Field &field) {
        switch (field.which) {
            case types::null:
                f(field.template get<null>());
                return;
            case types::uint64:
                f(field.template get<uint64>());
                return;
            case types::uint128:
                f(field.template get<uint128>());
                return;
            case types::int64:
                f(field.template get<Int64>());
                return;
            case types::float64:
                f(field.template get<float64>());
                return;

            case types::string:
                f(field.template get<string>());
                return;
            case types::array:
                f(field.template get<array>());
                return;
            case types::object:
                f(field.template get<object>());
                return;

            default:
                throw Exception("Bad type of Field", ErrorCodes::BAD_TYPE_OF_FIELD);
        }
    }


    class field {

        template<typename T>
        struct type_to_enum;
        template<types which>
        struct EnumToType;

        field() :
                which(types::null) {
        }

        /** Despite the presence of a template constructor, this constructor is still needed,
          *  since, in its absence, the compiler will still generate the default constructor.
          */
        field(const field &rhs) {
            create(rhs);
        }

        field(field &&rhs) {
            create(std::move(rhs));
        }

        template<typename T>
        field(T &&rhs, std::integral_constant<int, field::type_to_enum<std::decay<T>>::value> * = nullptr) {
            create_concrete(std::forward<T>(rhs));
        }

        field(const char *data, size_t size) {
            create(data, size);
        }

        field(const unsigned char *data, size_t size) {
            create(data, size);
        }

        void assign_string(const char *data, size_t size) {
            destroy();
            create(data, size);
        }

        void assign_string(const unsigned char *data, size_t size) {
            destroy();
            create(data, size);
        }

        field &operator=(const field &rhs) {
            if (this != &rhs) {
                if (which != rhs.which) {
                    destroy();
                    create(rhs);
                } else {
                    assign(rhs);    /// This assigns string or vector without deallocation of existing buffer.
                }
            }
            return *this;
        }

        field &operator=(field &&rhs) {
            if (this != &rhs) {
                if (which != rhs.which) {
                    destroy();
                    create(std::move(rhs));
                } else {
                    assign(std::move(rhs));
                }
            }
            return *this;
        }

        template<typename T>
        std::enable_if_t<!std::is_same<std::decay<T>, field>, field &>
        operator=(T &&rhs) {
            if (which != type_to_enum<std::decay<T>>::value) {
                destroy();
                create_concrete(std::forward<T>(rhs));
            } else {
                assign_concrete(std::forward<T>(rhs));
            }

            return *this;
        }

        ~Field() {
            destroy();
        }


        types get_type() const { return which; }

        const char *get_type_name() const { return to_string(which); }

        bool is_null() const { return which == types::null; }


        template<typename T>
        T &get() {
            using TWithoutRef = std::remove_reference<T>;
            TWithoutRef *ptr = reinterpret_cast<TWithoutRef *>(&storage);
            return *ptr;
        };

        template<typename T>
        const T &get() const {
            using TWithoutRef = std::remove_reference<T>;
            const TWithoutRef *ptr = reinterpret_cast<const TWithoutRef *>(&storage);
            return *ptr;
        };

        template<typename T>
        bool try_get(T &result) {
            const types requested = type_to_enum<std::decay<T>>::value;
            if (which != requested)
                return false;
            result = get<T>();
            return true;
        }

        template<typename T>
        bool try_get(T &result) const {
            const types requested = type_to_enum<std::decay<T>>::value;
            if (which != requested)
                return false;
            result = get<T>();
            return true;
        }

        template<typename T>
        T &safe_get() {
            const types requested = type_to_enum<std::decay<T>>::value;
            if (which != requested)
                throw Exception("Bad get: has " + std::string(get_type_name()) + ", requested " + std::string(to_string(requested)), ErrorCodes::BAD_GET);
            return get<T>();
        }

        template<typename T>
        const T &safe_get() const {
            const types requested = type_to_enum<std::decay<T>>::value;
            if (which != requested)
                throw std::exception("Bad get: has " + std::string(get_type_name()) + ", requested " + std::string(to_string(requested)), ErrorCodes::BAD_GET);
            return get<T>();
        }


        bool operator<(const field &rhs) const {
            if (which < rhs.which)
                return true;
            if (which > rhs.which)
                return false;

            switch (which) {
                case types::null:
                    return false;
                case types::uint64:
                    return get<uint64>() < rhs.get<uint64>();
                case types::uint128:
                    return get<uint128>() < rhs.get<uint128>();
                case types::int64:
                    return get<int64>() < rhs.get<int64>();
                case types::float64:
                    return get<float64>() < rhs.get<float64>();
                case types::string:
                    return get<string>() < rhs.get<string>();
                case types::array:
                    return get<array>() < rhs.get<array>();
                case types::object:
                    return get<object>() < rhs.get<object>();

                default:
                    throw Exception("Bad type of Field", ErrorCodes::BAD_TYPE_OF_FIELD);
            }
        }

        bool operator>(const field &rhs) const {
            return rhs < *this;
        }

        bool operator<=(const field &rhs) const {
            if (which < rhs.which)
                return true;
            if (which > rhs.which)
                return false;

            switch (which) {
                case types::null:
                    return true;
                case types::uint64:
                    return get<uint64>() <= rhs.get<uint64>();
                case types::uint128:
                    return get<UInt128>() <= rhs.get<UInt128>();
                case types::int64:
                    return get<Int64>() <= rhs.get<Int64>();
                case types::float64:
                    return get<float64>() <= rhs.get<float64>();
                case types::string:
                    return get<string>() <= rhs.get<string>();
                case types::array:
                    return get<array>() <= rhs.get<array>();
                case types::object:
                    return get<object>() <= rhs.get<object>();

                default:
                    throw Exception("Bad type of Field", ErrorCodes::BAD_TYPE_OF_FIELD);
            }
        }

        bool operator>=(const field &rhs) const {
            return rhs <= *this;
        }

        bool operator==(const field &rhs) const {
            if (which != rhs.which)
                return false;

            switch (which) {
                case types::null:
                    return true;
                case types::uint64:
                case types::int64:
                case types::float64:
                    return get<uint64>() == rhs.get<uint64>();
                case types::string:
                    return get<string>() == rhs.get<string>();
                case types::array:
                    return get<array>() == rhs.get<array>();
                case types::object:
                    return get<object>() == rhs.get<object>();
                case types::uint128:
                    return get<uint128>() == rhs.get<uint128>();

                default:
                    throw Exception("Bad type of Field", ErrorCodes::BAD_TYPE_OF_FIELD);
            }
        }

        bool operator!=(const field &rhs) const {
            return !(*this == rhs);
        }

    private:
        std::aligned_union<
                DBMS_MIN_FIELD_SIZE - sizeof(types),
                types::null,
                types::uint64,
                types::uint128,
                types::int64,
                types::float64,
                types::string,
                types::array,
                types::object
        > storage;

        types which;


        template<typename T>
        void create_concrete(T &&x) {
            using JustT = std::decay<T>;
            JustT *ptr = reinterpret_cast<JustT *>(&storage);
            new(ptr) JustT(std::forward<T>(x));
            which = type_to_enum<JustT>::value;
        }

        template<typename T>
        void assign_concrete(T &&x) {
            using JustT = std::decay<T>;
            JustT *ptr = reinterpret_cast<JustT *>(&storage);
            *ptr = std::forward<T>(x);
        }

        void create(const field &x) {
            dispatch([this](auto &value) { create_concrete(value); }, x);
        }

        void create(field &&x) {
            dispatch([this](auto &value) { create_concrete(std::move(value)); }, x);
        }

        void assign(const field &x) {
            dispatch([this](auto &value) { assign_concrete(value); }, x);
        }

        void assign(field &&x) {
            dispatch([this](auto &value) { assign_concrete(std::move(value)); }, x);
        }


        void create(const char *data, size_t size) {
            string * ptr = reinterpret_cast<string *>(&storage);
            new(ptr) string(data, size);
            which = types::string;
        }

        void create(const unsigned char *data, size_t size) {
            create(reinterpret_cast<const char *>(data), size);
        }

        void destroy() {
            if (which < MIN_NON_POD)
                return;

            switch (which) {
                case types::string:
                    destroy < string > ();
                    break;
                case types::array:
                    destroy < array > ();
                    break;
                case types::object:
                    destroy < object > ();
                    break;
                default:
                    break;
            }

            which = types::null;    /// for exception safety in subsequent calls to destroy and create, when create fails.
        }

        template<typename T>
        void destroy() {
            T *ptr = reinterpret_cast<T *>(&storage);
            ptr->~T();
        }
    };

#undef DBMS_MIN_FIELD_SIZE

    template<>
    struct Field::type_to_enum<null> {
        static const types value = types::null;
    };
    template<>
    struct Field::type_to_enum<uint64> {
        static const types value = types::uint64;
    };
    template<>
    struct Field::type_to_enum<uint128> {
        static const types value = types::uint128;
    };
    template<>
    struct Field::type_to_enum<Int64> {
        static const types value = types::int64;
    };
    template<>
    struct Field::type_to_enum<float64> {
        static const types value = types::float64;
    };
    template<>
    struct Field::type_to_enum<string> {
        static const types value = types::string;
    };
    template<>
    struct Field::type_to_enum<array> {
        static const types value = types::array;
    };
    template<>
    struct Field::type_to_enum<object> {
        static const types value = types::object;
    };

    template<>
    struct Field::enum_to_type<types::null> {
        using Type = null;
    };
    template<>
    struct Field::enum_to_type<types::uint64> {
        using Type = uint64;
    };
    template<>
    struct Field::enum_to_type<types::uint128> {
        using Type = uint128;
    };
    template<>
    struct Field::enum_to_type<types::int64> {
        using Type = Int64;
    };
    template<>
    struct Field::enum_to_type<types::float64> {
        using Type = float64;
    };
    template<>
    struct Field::enum_to_type<types::string> {
        using Type = string;
    };
    template<>
    struct Field::enum_to_type<types::array> {
        using Type = array;
    };
    template<>
    struct Field::enum_to_type<types::object> {
        using Type = object ;
    };


    template<typename T>
    T get(const field &field_) {
        return field_.template get<T>();
    }

    template<typename T>
    T get(field &field_) {
        return field_.template get<T>();
    }

    template<typename T>
    T safe_get(const field &field_) {
        return field_.template safe_get<T>();
    }

    template<typename T>
    T safe_get(field &field_) {
        return field_.template safe_get<T>();
    }


    template<>
    struct type_name<array> {
        static std::string get() { return "array"; }
    };

    template<>
    struct type_name<object> {
        static std::string get() { return "object"; }
    };


    template<typename T>
    struct nearest_field_type;

    template<>
    struct nearest_field_type<uint8> {
        using Type = uint64;
    };
    template<>
    struct nearest_field_type<uint16> {
        using Type = uint64;
    };
    template<>
    struct nearest_field_type<uint32> {
        using Type = uint64;
    };
    template<>
    struct nearest_field_type<uint64> {
        using Type = uint64;
    };
    template<>
    struct nearest_field_type<uint128> {
        using Type = uint128;
    };
    template<>
    struct nearest_field_type<int8> {
        using Type = Int64;
    };
    template<>
    struct nearest_field_type<Int16> {
        using Type = Int64;
    };
    template<>
    struct nearest_field_type<Int32> {
        using Type = Int64;
    };
    template<>
    struct nearest_field_type<Int64> {
        using Type = Int64;
    };
    template<>
    struct nearest_field_type<float32> {
        using Type = float64;
    };
    template<>
    struct nearest_field_type<float64> {
        using Type = float64;
    };
    template<>
    struct nearest_field_type<string> {
        using Type = string;
    };
    template<>
    struct nearest_field_type<array> {
        using Type = array;
    };
    template<>
    struct nearest_field_type<object> {
        using Type = object;
    };
    template<>
    struct nearest_field_type<bool> {
        using Type = uint64;
    };
    template<>
    struct nearest_field_type<null> {
        using Type = null;
    };


    template<typename T>
    typename nearest_field_type<T>::Type nearest_field_type(const T &x) {
        return typename nearest_field_type<T>::Type(x);
    }


}
#endif
