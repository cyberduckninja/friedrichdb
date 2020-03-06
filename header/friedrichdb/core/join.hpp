#pragma once

#include <vector>
#include <friedrichdb/core/schema.hpp>

namespace friedrichdb { namespace core {

enum class join_type {
  left,
  right,
  inner,
  full_outer
};

template <
    template <typename A> class Allocator,
    template <typename P, class D> class UniquePtr
>
class collection;

template <
    template <typename A> class Allocator1,
    template <typename A> class Allocator2,
    template <typename P, class D> class UniquePtr1,
    template <typename P, class D> class UniquePtr2
>
auto left_join(
    std::vector<std::string> &keys,
    const collection<Allocator1, UniquePtr1> &c1,
    const collection<Allocator2, UniquePtr2> &c2
) -> void {

  for (auto &i : c1.schema()) {
    keys.push_back(i.name_);
  }
}

}}