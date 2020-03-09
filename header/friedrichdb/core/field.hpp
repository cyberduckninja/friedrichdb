#pragma once

#include "basic_field.hpp"

namespace friedrichdb { namespace core {

template<
    template <typename P> class Allocator,
    template <typename P,class D> class UniquePtr
>
struct field_t final {
  using field = basic_field<Allocator, UniquePtr>;
  using string_t = typename field::string_t ;
  string_t uuid;
  field base_;
};

template <
    template <typename P> class Allocator,
    template <typename P,class D> class UniquePtr
>
struct field_metadata final {
  using field_t = basic_field<Allocator, UniquePtr>;
  using string_t = typename field_t::string_t ;

  field_metadata(const string_t &name, field_type type)
      : name_(name), type_(type) {}

  string_t name_;
  field_type type_;
};

}}