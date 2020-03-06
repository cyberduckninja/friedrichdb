#pragma once

#include "basic_field.hpp"

namespace friedrichdb { namespace core {

template <template <typename P> class Allocator> class basic_schema_t final {
public:
  using storage_t = basic_vector_t<field_metadata<Allocator>, Allocator>;
  using iterator = typename storage_t::iterator;
  using const_iterator = typename storage_t::const_iterator;
  using string_t = basic_string_t<char, std::char_traits, Allocator>;
  using index_t =
      basic_map_t<
          string_t,
          std::size_t,
          std::less<>,
          Allocator<std::pair<const string_t, std::size_t>>>;

  basic_schema_t() = default;

  template <class Iterator>
  basic_schema_t(Iterator begin, Iterator end) : storage_() {
    storage_.insert(storage_.cend(), begin, end);
    int index = 0;
    for (auto &i : storage_) {
      index_.emplace(i.name_, index);
      ++index;
    }
  }

  const field_type &field(std::size_t index) const {
    return storage_.at(index);
  }

  const field_type &field(const std::string &index) const {
    return storage_.at(index_.at(index));
  }

  void push(const string_t &name, field_type type) {
    storage_.emplace_back(name, type);
    index_.emplace(name, storage_.size());
  }

  auto begin() -> iterator { return storage_.begin(); }

  auto end() -> iterator { return storage_.end(); }

  auto begin() const -> const_iterator { return storage_.begin(); }

  auto end() const -> const_iterator { return storage_.end(); }

private:
  storage_t storage_;
  index_t index_;
};

template<template<typename P> class Allocator>
using empty_basic_schema_t = basic_schema_t<Allocator>;

}}