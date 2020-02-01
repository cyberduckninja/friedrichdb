#pragma once

#include <memory>
#include <vector>
#include <map>
#include <unordered_map>
#include <string>
#include <cassert>


class number final {
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
    number(const number&) = delete;
    number&operator=(const number&) = delete;
    explicit number(std::uint8_t value):type_(type::uint8),payload_(value) {}
    explicit number(std::uint16_t value):type_(type::uint16),payload_(value) {}
    explicit number(std::uint32_t value):type_(type::uint32),payload_(value) {}
    explicit number(std::uint64_t value):type_(type::uint64),payload_(value) {}
    explicit number(std::int8_t value):type_(type::int8),payload_(value) {}
    explicit number(std::int16_t value):type_(type::int16),payload_(value) {}
    explicit number(std::int32_t value):type_(type::int32),payload_(value) {}
    explicit number(std::int64_t value):type_(type::int64),payload_(value) {}
    explicit number(float value):type_(type::float32),payload_(value) {}
    explicit number(double value):type_(type::float64),payload_(value) {}

    bool operator < (const number & rhs) const {

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

    bool operator> (const number & rhs) const{
        return rhs < *this;
    }

    bool operator<= (const number & rhs) const{

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

    bool operator>= (const number & rhs) const{
        return rhs <= *this;
    }

    bool operator == (const number & rhs) const {

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

    bool operator!= (const number & rhs) const{
        return !(*this == rhs);
    }

private:
    type type_;
    payload payload_;
};


class flat_field;
using array = std::vector<flat_field>;

class flat_field final {
private:
    enum class type : uint8_t {
        null_t,
        bool_t,
        number_t,
        string_t,
    };

    union payload {

        payload():nullptr_(){}

        explicit payload(bool value):bool_(value){}

        template <class T, bool flag= std::is_scalar<T>::value>
        explicit payload(T value):number_(new number(value)){}

        payload(const std::string& value):string_(new std::string(value)){}

        std::nullptr_t nullptr_;
        bool bool_;
        number* number_;
        std::string* string_;
    };

public:

    flat_field(const flat_field&) = delete;

    flat_field&operator=(const flat_field&) = delete;

    flat_field(): type_(type::null_t), payload_(std::make_unique<payload>()){}

    flat_field(bool value): type_(type::bool_t), payload_(std::make_unique<payload>(value)){}

    template <class T, class = std::is_scalar<T>>
    flat_field(T value): type_(type::number_t), payload_(std::make_unique<payload>(value)){}

    flat_field(const std::string& value): type_(type::string_t), payload_(std::make_unique<payload>(value)){}

    ///flat_field(const char* value): type_(type::string_t), payload_(std::make_unique<payload>(value)){}

    bool is_string() noexcept {
        return type_ == type::string_t;
    }

    bool is_number() noexcept {
        return type_ == type::number_t;
    }

    bool is_bool() noexcept {
        return type_ == type::bool_t;
    }

    number & get_number() const {
        assert(type_ == type::number_t);
        return *(payload_->number_);
    }

    bool get_bool() const {
        assert(type_ == type::bool_t);
        return payload_->bool_;
    }

    std::string& get_string() const {
        assert(type_ == type::string_t);
        return *(payload_->string_);
    }

    std::string& get_string(){
        assert(type_ == type::string_t);
        return *(payload_->string_);
    }

    bool operator< (const flat_field & rhs) const {

        switch (type_){
            case type::null_t:   return false;
            case type::number_t: return get_number() < rhs.get_number();
            case type::string_t: return get_string() < rhs.get_string();
            case type::bool_t:   return get_bool()   < rhs.get_bool();

        }

    }

    bool operator> (const flat_field & rhs) const {
        return rhs < *this;
    }

    bool operator<= (const flat_field & rhs) const {

        switch (type_){
            case type::null_t:   return true;
            case type::number_t: return get_number() <= rhs.get_number();
            case type::string_t: return get_string() <= rhs.get_string();
            case type::bool_t:   return get_bool()   <= rhs.get_bool();
        }

    }

    bool operator>= (const flat_field & rhs) const{
        return rhs <= *this;
    }

    bool operator == (const flat_field & rhs) const {
        if (type_ != rhs.type_)
            return false;

        switch (type_){
            case type::null_t:   return true;
            case type::number_t: return get_number() == rhs.get_number();
            case type::string_t: return get_string() == rhs.get_string();
            case type::bool_t:   return get_bool()   == rhs.get_bool();
        }

    }

    bool operator!= (const flat_field & rhs) const{
        return !(*this == rhs);
    }


private:
    type type_;
    std::unique_ptr<payload> payload_;

};




