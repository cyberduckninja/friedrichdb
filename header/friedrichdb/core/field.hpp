#pragma once
#include "friedrichdb/core/type.hpp"

namespace friedrichdb { namespace core {

template <template <typename P> class Allocator>
struct field final {
  using string_t = basic_string_t<char, std::char_traits, Allocator>;
  string_t uuid;
  field_base base_;
};

template <template <typename P> class Allocator>
struct field_metadata final {
  using string_t = basic_string_t<char, std::char_traits, Allocator>;

  field_metadata(const string_t &name, field_type type)
      : name_(name), type_(type) {}

  string_t name_;
  field_type type_;
};

}}