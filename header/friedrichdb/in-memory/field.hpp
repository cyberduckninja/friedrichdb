#pragma once

#include <vector>
#include <map>
#include <unordered_map>
#include <string>


template<class T>
class incomplete_wrapper {
public:

    incomplete_wrapper() = default;

    incomplete_wrapper(const incomplete_wrapper &) {}

    incomplete_wrapper &operator=(const incomplete_wrapper &) {
        return *this;
    }

    T &get() {
        return *data_;
    }

    const T &get() const {
        return *data_;
    }

    template<class... Args>
    void set(Args &&... args) {
        data_.reset(new T(std::forward<Args>(args)...));
    }

private:
    std::unique_ptr<T> data_;
};

class number final {
private:
    enum class type_t : char {
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
        std::uint8_t payload_uint8_t;
        std::uint16_t payload_uint16_t;
        std::uint32_t payload_uint32_t;
        std::uint64_t payload_uint64_t;
        std::int8_t payload_int8_t;
        std::int16_t payload_int16_t;
        std::int32_t payload_int32_t;
        std::int64_t payload_int64_t;
        float payload_float;
        double payload_double;
    };
};

class field final {
public:
    field(std::nullptr_t);
    enum class type : char {
        null_t,
        bool_t,
        number_t,
        string_t,
        array_t,
        map_t,
        hash_map_t
    };

    union payload {
        explicit payload() : payload_nullptr(nullptr) {}
        ~payload() = default;

        std::nullptr_t payload_nullptr;
        bool payload_bool;
        number payload_number;
        incomplete_wrapper<std::string> payload_string;
        incomplete_wrapper<std::vector<field>> payload_vector;
        incomplete_wrapper<std::map<std::string, field>> payload_map;
        incomplete_wrapper<std::unordered_map<std::string, field>> payload_hash_map;
    };

private:

    type type_;
    payload payload_;

};

field::field(std::nullptr_t):type_(type::null_t) {

}


