#pragma once

template<
    template<typename A> class OtherAllocator,
    template <typename P,class D> class OtherUniquePtr
>
void update(
    const collection<OtherAllocator,OtherUniquePtr> &other,
    join_type join = join_type::left,
    bool overwrite = true
) { ///, filter_func=None, errors='ignore'))
  std::vector<std::string> key;

  switch (join) {
  case join_type::left:
    left_join(key, this, other);
    break;
  case join_type::right:
    break;
  case join_type::inner:
    break;
  case join_type::full_outer:
    break;
  }

  for(const auto&i:key){

  }


}