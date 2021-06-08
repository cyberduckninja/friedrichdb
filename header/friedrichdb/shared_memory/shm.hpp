#include <boost/interprocess/allocators/allocator.hpp>
#include <boost/interprocess/managed_shared_memory.hpp>
#include <boost/interprocess/smart_ptr/unique_ptr.hpp>
#include <boost/container/list.hpp>

#include "friedrichdb/core/basic_field.hpp"



namespace friedrichdb { namespace shared_memory {

        namespace bip = boost::interprocess;
        using boost::interprocess::managed_unique_ptr;
        using boost::interprocess::make_managed_unique_ptr;

        using segment_t = bip::managed_shared_memory;
        using manager_t = typename segment_t::segment_manager;

        template<typename T>
        using allocator_t = bip::allocator<T, manager_t>;

        template<class Key, class T>
        using map_shm = core::basic_map_t<Key, T, std::less<>, allocator_t<std::pair<const Key, T>>>;

        template<typename T>
        using list_shm = boost::container::list<T, allocator_t<T>>;

        template<class T>
        using vector_shm = core::basic_vector_t<T,allocator_t>;

        using string_shm = core::basic_string_t<char, std::char_traits, allocator_t>;

        template<typename K, typename V, typename KH = std::hash<K>, typename KEq = std::equal_to<K> >
        using unordered_map_shm = boost::unordered_map<K, V, KH, KEq, allocator_t<std::pair<const K, V>>>;

        template<typename K, typename Manager>
        using unique_ptr_shm = typename managed_unique_ptr<K, Manager>::type;

/// template<class T>
/// using make_unique_ptr_shm = make_managed_unique_ptr<T,manager>;


        template<class T>
        class incomplete_wrapper final {
        public:

            incomplete_wrapper() = default;

            incomplete_wrapper(const incomplete_wrapper &) {}

            incomplete_wrapper &operator=(const incomplete_wrapper &) {
                return *this;
            }

            T &get() {
                return *data_;
            }

            const T &get() const {
                return *data_;
            }

            template<class... Args>
            void set(Args &&... args) {
                data_ = make_managed_unique_ptr<T>(std::forward<Args>(args)...);
            }


        private:
            unique_ptr_shm<T, manager_t> data_;
        };


        using field_base_shm = core::basic_field<allocator_t, unique_ptr_shm>;

        using  big_object  = map_shm<string_shm,vector_shm<uint8_t>>;

        using void_allocator = allocator_t<void>;

        class database_shm final {
        public:
            database_shm() = delete;
            database_shm(const char *name)
                : segment_(
                    boost::interprocess::open_or_create,
                    name,
                    65536)
                , allocator(segment_ .get_segment_manager()) {

            }
        private:
            boost::interprocess::managed_shared_memory segment_;
            void_allocator allocator;
            ///list_shm<unique_ptr_shm<big_object,manager_t>> storage_;
        };
}}