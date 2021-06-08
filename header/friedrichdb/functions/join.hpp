#pragma once

#include <vector>

#include "forward.hpp"
#include <friedrichdb/core/schema.hpp>
#include <friedrichdb/core/collection.hpp>

namespace friedrichdb { namespace functions {

enum class join_type { left, right, inner, full_outer };

template <
    template <typename A> class Allocator1,
    template <typename A> class Allocator2,
    template <typename P, class D> class UniquePtr1,
    template <typename P, class D> class UniquePtr2
>
auto left_join(std::vector<std::string> &keys,
               const core::collection<Allocator1, UniquePtr1> &c1,
               const core::collection<Allocator2, UniquePtr2> &c2) -> void {

  for (auto &i : c1.schema()) {
    keys.push_back(i.name_);
  }
}

template <
    template <typename A> class Allocator1,
    template <typename A> class Allocator2,
    template <typename P, class D> class UniquePtr1,
    template <typename P, class D> class UniquePtr2
>
auto inner_join(
    std::vector<std::string> &keys,
    const core::collection<Allocator1, UniquePtr1> &c1,
    const core::collection<Allocator2, UniquePtr2> &c2
) -> void {

}

}}