#pragma once

#include <boost/make_unique.hpp>
#include <boost/interprocess/containers/map.hpp>
#include <boost/interprocess/containers/vector.hpp>
#include <boost/interprocess/containers/string.hpp>
#include <boost/interprocess/smart_ptr/unique_ptr.hpp>

namespace friedrichdb { namespace core {

        template<class T, template<typename P> class Allocator>
        struct basic_tensor_t final {
            boost::container::vector<unsigned int, Allocator<unsigned int>> shape_;
            boost::container::vector<T, Allocator<T>> base_;
        };

        template<typename CharT, template<typename T> class Traits,
                template<typename T> class Allocator> ///std::char_traits<CharT>
        using basic_string_t = boost::container::basic_string<CharT, Traits<CharT>, Allocator<CharT>>;

        template<typename T, template<typename P> class Allocator>
        using basic_vector_t =  boost::container::vector<T, Allocator<T>>;

        template<class Key, class T, class Compare, class Allocator>
        using basic_map_t = boost::container::map<Key, T, Compare, Allocator>;

        template<class T, class D = boost::movelib::default_delete<T> >
        using unique_ptr_t =  boost::interprocess::unique_ptr<T, D>;
    }}