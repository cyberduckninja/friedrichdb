#pragma once

#include <boost/make_unique.hpp>
#include <boost/interprocess/containers/map.hpp>
#include <boost/interprocess/containers/vector.hpp>
#include <boost/interprocess/containers/string.hpp>
#include <boost/unordered_map.hpp>
#include <boost/utility/string_view.hpp>

namespace friedrichdb::core {

    template<
            class CharT,
            class Traits = std::char_traits<CharT>,
            class Allocator  = void
    >
    using basic_string_t = boost::container::basic_string<CharT, Traits, Allocator>;

    using boost::basic_string_view;

    template<
            class T,
            class Allocator = void
    >
    using basic_vector_t = boost::container::vector<T, Allocator>;

    template<
            class Key,
            class T,
            class Compare  = std::less<Key>,
            class Allocator = void
    >
    using basic_map_t = boost::container::map<Key, T, Compare, Allocator>;


    template<
            class Key,
            class Value,
            class H = boost::hash<Key>,
            class P = std::equal_to<Key>,
            class A = std::allocator<std::pair<const Key, Value> >
    >
    using basic_unordered_map_t = boost::unordered_map<Key, Value, H, P, A>;

}