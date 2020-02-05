#pragma once

#include <cassert>
#include <boost/make_unique.hpp>
#include <boost/interprocess/containers/map.hpp>
#include <boost/interprocess/containers/vector.hpp>
#include <boost/interprocess/containers/string.hpp>
#include <boost/interprocess/smart_ptr/unique_ptr.hpp>

class field_base;
///TODO:
struct tensor_base final {
    boost::container::vector<unsigned int> shape_;
    boost::container::vector<field_base> base_;
};

using string_t = boost::container::string;
using array_t =  boost::container::vector<field_base>;
using object_t = boost::container::map<string_t,field_base>; /// hashmap
using tensor_t = tensor_base;

enum class field_type : uint8_t {
    null_t,
    bool_t,
    number_t,
    string_t,
    array_t,
    object_t

};

/// TODO:  decimal
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
    number() = default;
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


class field_base final {

    union payload {

        payload():nullptr_(){}

        explicit payload(bool value):bool_(value){}

        template <class T,  typename = typename std::enable_if<std::is_arithmetic<T>::value>::type>
        explicit payload(T value):number_(new number(value)){}

        payload(const string_t & value):string_(new string_t(value)){}

        std::nullptr_t nullptr_;
        bool bool_;
        number* number_;
        string_t* string_;
        array_t* array_;
        object_t* object_;
    };

public:
    using key_type = string_t;
    using mapped_type = field_base;
    using value_type = boost::container::pair<const key_type,mapped_type>;
    using reference = field_base&;
    using const_reference = const field_base&;
    using size_type = std::size_t ;

    static auto  array() -> field_base {
        return field_base(field_type::array_t);
    }

    static auto  object() -> field_base {
        return field_base(field_type::object_t);
    }

    field_base(const field_base&) = delete;

    field_base&operator=(const field_base&) = delete;

    field_base(field_base&&) = default;
    field_base&operator=(field_base&&) = default;

    ~field_base() {
        reset();
    }

    field_base(): type_(field_type::null_t), payload_(new payload){}

    field_base(bool value): type_(field_type::bool_t), payload_(new payload(value)){}

    template <class T,  typename = typename std::enable_if<std::is_arithmetic<T>::value>::type>
    field_base(T value): type_(field_type::number_t), payload_(new payload(value)){}

    field_base(const string_t & value): type_(field_type::string_t), payload_(new payload(value)){}

    field_base(const char* value): type_(field_type::string_t), payload_(new payload(value)){}

    bool is_string() const noexcept {
        return type_ == field_type::string_t;
    }

    bool is_number() const noexcept {
        return type_ == field_type::number_t;
    }

    bool is_bool() const noexcept {
        return type_ == field_type::bool_t;
    }

    bool is_array() const noexcept {
        return type_ == field_type::array_t;
    }

    bool is_object() const noexcept {
        return type_ == field_type::object_t;
    }

    mapped_type& at(const key_type& k) const {
        return get_object().at(k);
    }

    template<typename... Args>
    void emplace(Args&&... args){
        get_object().emplace(std::forward<Args>(args)...);
    }

    const_reference at (size_type n) const {
        return get_array().at(n);
    }

    template<typename... Args>
    reference emplace_back(Args&&... args){
        return get_array().emplace_back(std::forward<Args>(args)...);
    }

    bool operator< (const field_base & rhs) const {

        switch (type_){
            case field_type::null_t:   return false;
            case field_type::number_t: return get_number() < rhs.get_number();
            case field_type::string_t: return get_string() < rhs.get_string();
            case field_type::bool_t:   return get_bool()   < rhs.get_bool();

        }

    }

    bool operator> (const field_base & rhs) const {
        return rhs < *this;
    }

    bool operator<= (const field_base & rhs) const {

        switch (type_){
            case field_type::null_t:   return true;
            case field_type::number_t: return get_number() <= rhs.get_number();
            case field_type::string_t: return get_string() <= rhs.get_string();
            case field_type::bool_t:   return get_bool()   <= rhs.get_bool();
        }

    }

    bool operator>= (const field_base & rhs) const{
        return rhs <= *this;
    }

    bool operator == (const field_base & rhs) const {
        if (type_ != rhs.type_)
            return false;

        switch (type_){
            case field_type::null_t:   return true;
            case field_type::number_t: return get_number() == rhs.get_number();
            case field_type::string_t: return get_string() == rhs.get_string();
            case field_type::bool_t:   return get_bool()   == rhs.get_bool();
        }

    }

    bool operator!= (const field_base & rhs) const{
        return !(*this == rhs);
    }


private:

    void reset() {

        switch (type_){
            case field_type::array_t:
                delete payload_->array_;
            case field_type::object_t:
                delete payload_->object_;
            type_ = field_type::null_t;
            return;
        }

    }

    void create(field_type crete_type){
        payload_.reset(new payload);
        switch (crete_type){
            case field_type::array_t:
                type_= field_type::array_t;
                payload_->array_ = new array_t;
                break;
            case field_type::object_t:
                type_ = field_type::object_t;
                payload_->object_ = new object_t;
                break;
            case field_type::null_t:
                type_ = field_type::null_t;
                break;
            case field_type::bool_t:
                type_ = field_type::bool_t;
                break;
            case field_type::number_t:
                type_ = field_type::number_t;
                ///payload_->number_ = new number;
                break;
            case field_type::string_t:
                type_ = field_type::string_t;
                payload_->string_ = new string_t;
                break;
        }
    }

    field_base(field_type type){
        create(type);
    }

    number & get_number() const {
        assert(type_ == field_type::number_t);
        return *(payload_->number_);
    }

    bool get_bool() const {
        assert(type_ == field_type::bool_t);
        return payload_->bool_;
    }

    string_t & get_string() const {
        assert(type_ == field_type::string_t);
        return *(payload_->string_);
    }

    string_t & get_string(){
        assert(type_ == field_type::string_t);
        return *(payload_->string_);
    }

    object_t & get_object(){
        assert(type_ == field_type::object_t);
        return *(payload_->object_);
    }

    object_t & get_object() const {
        assert(type_ == field_type::object_t);
        return *(payload_->object_);
    }

    array_t & get_array(){
        assert(type_ == field_type::array_t);
        return *(payload_->array_);
    }

    array_t & get_array() const {
        assert(type_ == field_type::array_t);
        return *(payload_->array_);
    }

    field_type type_;
    boost::interprocess::unique_ptr<payload> payload_;

};




