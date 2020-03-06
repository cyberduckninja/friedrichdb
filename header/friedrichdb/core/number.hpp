#pragma once

namespace friedrichdb { namespace core {

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
    explicit payload(std::uint8_t value) : uint8(value) {}

    explicit payload(std::uint16_t value) : uint16(value) {}

    explicit payload(std::uint32_t value) : uint32(value) {}

    explicit payload(std::uint64_t value) : uint64(value) {}

    explicit payload(std::int8_t value) : int8(value) {}

    explicit payload(std::int16_t value) : int16(value) {}

    explicit payload(std::int32_t value) : int32(value) {}

    explicit payload(std::int64_t value) : int64(value) {}

    explicit payload(float value) : float32(value) {}

    explicit payload(double value) : float64(value) {}

    std::uint8_t uint8;
    std::uint16_t uint16;
    std::uint32_t uint32;
    std::uint64_t uint64;
    std::int8_t int8;
    std::int16_t int16;
    std::int32_t int32;
    std::int64_t int64;
    float float32;
    double float64;
  };

public:
  number_t() = default;

  number_t(const number_t &) = delete;

  number_t &operator=(const number_t &) = delete;

  explicit number_t(std::uint8_t value) : type_(type::uint8), payload_(value) {}

  explicit number_t(std::uint16_t value)
      : type_(type::uint16), payload_(value) {}

  explicit number_t(std::uint32_t value)
      : type_(type::uint32), payload_(value) {}

  explicit number_t(std::uint64_t value)
      : type_(type::uint64), payload_(value) {}

  explicit number_t(std::int8_t value) : type_(type::int8), payload_(value) {}

  explicit number_t(std::int16_t value) : type_(type::int16), payload_(value) {}

  explicit number_t(std::int32_t value) : type_(type::int32), payload_(value) {}

  explicit number_t(std::int64_t value) : type_(type::int64), payload_(value) {}

  explicit number_t(float value) : type_(type::float32), payload_(value) {}

  explicit number_t(double value) : type_(type::float64), payload_(value) {}

  bool operator<(const number_t &rhs) const {

    switch (type_) {
    case type::uint8:
      return payload_.uint8 < rhs.payload_.uint8;
    case type::uint16:
      return payload_.uint16 < rhs.payload_.uint32;
    case type::uint32:
      return payload_.uint32 < rhs.payload_.uint32;
    case type::uint64:
      return payload_.uint64 < rhs.payload_.uint64;
    case type::int8:
      return payload_.int8 < rhs.payload_.int8;
    case type::int16:
      return payload_.int16 < rhs.payload_.int16;
    case type::int32:
      return payload_.int32 < rhs.payload_.int32;
    case type::int64:
      return payload_.int64 < rhs.payload_.int64;
    case type::float32:
      return payload_.float32 < rhs.payload_.float32;
    case type::float64:
      return payload_.float64 < rhs.payload_.float64;
    }
  }

  bool operator>(const number_t &rhs) const { return rhs < *this; }

  bool operator<=(const number_t &rhs) const {

    switch (type_) {
    case type::uint8:
      return payload_.uint8 <= rhs.payload_.uint8;
    case type::uint16:
      return payload_.uint16 <= rhs.payload_.uint32;
    case type::uint32:
      return payload_.uint32 <= rhs.payload_.uint32;
    case type::uint64:
      return payload_.uint64 <= rhs.payload_.uint64;
    case type::int8:
      return payload_.int8 <= rhs.payload_.int8;
    case type::int16:
      return payload_.int16 <= rhs.payload_.int16;
    case type::int32:
      return payload_.int32 <= rhs.payload_.int32;
    case type::int64:
      return payload_.int64 <= rhs.payload_.int64;
    case type::float32:
      return payload_.float32 <= rhs.payload_.float32;
    case type::float64:
      return payload_.float64 <= rhs.payload_.float64;
    }
  }

  bool operator>=(const number_t &rhs) const { return rhs <= *this; }

  bool operator==(const number_t &rhs) const {

    switch (type_) {
    case type::uint8:
      return payload_.uint8 == rhs.payload_.uint8;
    case type::uint16:
      return payload_.uint16 == rhs.payload_.uint32;
    case type::uint32:
      return payload_.uint32 == rhs.payload_.uint32;
    case type::uint64:
      return payload_.uint64 == rhs.payload_.uint64;
    case type::int8:
      return payload_.int8 == rhs.payload_.int8;
    case type::int16:
      return payload_.int16 == rhs.payload_.int16;
    case type::int32:
      return payload_.int32 == rhs.payload_.int32;
    case type::int64:
      return payload_.int64 == rhs.payload_.int64;
    case type::float32:
      return payload_.float32 == rhs.payload_.float32;
    case type::float64:
      return payload_.float64 == rhs.payload_.float64;
    }
  }

  bool operator!=(const number_t &rhs) const { return !(*this == rhs); }

private:
  type type_;
  payload payload_;
};

}}