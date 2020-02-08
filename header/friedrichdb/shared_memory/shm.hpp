#include <boost/interprocess/allocators/allocator.hpp>
#include <boost/interprocess/managed_shared_memory.hpp>
#include <boost/interprocess/smart_ptr/unique_ptr.hpp>

#include "../core/type.hpp"

#include <unordered_map>

namespace bip = boost::interprocess;
using boost::interprocess::managed_unique_ptr;
using boost::interprocess::make_managed_unique_ptr;

using segment = bip::managed_shared_memory;
using manager = typename segment::segment_manager;

template<typename T>
using allocator = bip::allocator<T, manager>;

template <class Key, class T>
using map_shm = basic_map_t <Key,T,std::less<Key>,allocator<T>>;

template <class T>
using vector_shm = basic_vector_t<T,allocator>;

using string_shm = basic_string_t <char,std::char_traits,allocator>;

template <typename K, typename V, typename KH = std::hash<K>, typename KEq = std::equal_to<K> >
using unordered_map_shm = std::unordered_map<K, V, KH, KEq, allocator<std::pair<const K, V>> >;

template<typename K>
using unique_ptr_shm = typename managed_unique_ptr<K,manager>::type;

template<class T>
using make_unique_ptr_shm = make_managed_unique_ptr<T,manager>;


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
    unique_ptr_shm<T> data_;
};
