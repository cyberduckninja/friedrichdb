#include <boost/interprocess/containers/map.hpp>
#include <boost/interprocess/containers/vector.hpp>
#include <boost/interprocess/containers/string.hpp>
#include <boost/interprocess/smart_ptr/unique_ptr.hpp>


#include <boost/interprocess/allocators/allocator.hpp>
#include <boost/interprocess/sync/interprocess_sharable_mutex.hpp>
#include <boost/interprocess/managed_shared_memory.hpp>
#include <boost/core/demangle.hpp>

#include <boost/multi_index_container.hpp>

#include <boost/chrono.hpp>
#include <boost/config.hpp>
#include <boost/throw_exception.hpp>

#include <array>
#include <atomic>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <typeindex>
#include <typeinfo>
#include <unordered_map>

#include "node_allocator.hpp"


namespace bip = boost::interprocess;
using boost::interprocess::managed_unique_ptr;
using boost::interprocess::make_managed_unique_ptr;



using segment = bip::managed_shared_memory;
using manager = typename segment::segment_manager;

template<typename T>
using allocator = bip::allocator<T, manager>;

template<typename T>
using node_allocator = node_allocator<T, manager>;

template <class Key, class T>
using map_shared = boost::interprocess::map<Key,T,std::less<Key>,allocator<T>>;

template <class T>
using vector_shared = boost::interprocess::vector<T,allocator<T>>;

using string_shared = boost::interprocess::basic_string<char,std::char_traits<char>,allocator<char>>;

template <typename K, typename V, typename KH = std::hash<K>, typename KEq = std::equal_to<K> >
using unordered_map_shared = std::unordered_map<K, V, KH, KEq, allocator<std::pair<const K, V>> >;

template<typename K>
using unique_ptr_shared = typename managed_unique_ptr<K,manager>::type;

template<class T>
using make_managed_unique_ptr = make_managed_unique_ptr<T,manager>;


template<class T>
class incomplete_wrapper final {
public:

    incomplete_wrapper() = default;

    incomplete_wrapper(const incomplete_wrapper&) {}

    incomplete_wrapper& operator=(const incomplete_wrapper&) {
        return *this;
    }

    T& get() {
        return *data_;
    }

    const T& get() const {
        return *data_;
    }

    template<class... Args>
    void set(Args&&... args) {
        data_ = make_managed_unique_ptr<T>(std::forward<Args>(args)...);
    }


private:
    unique_ptr_shared<T> data_;
};
