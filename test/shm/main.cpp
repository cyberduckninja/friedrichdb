#include <friedrichdb/shared_memory/shm.hpp>
#include <iostream>

constexpr static char *name = "MySharedMemory";

struct shm_remove final {
    shm_remove() { boost::interprocess::shared_memory_object::remove(name); }

    ~shm_remove() { boost::interprocess::shared_memory_object::remove(name); }
};

using namespace friedrichdb::shared_memory;

using void_allocator = allocator_t<void>;



int main() {
    shm_remove remover;

    boost::interprocess::managed_shared_memory segment(
            boost::interprocess::open_or_create,
            name,
            65536
    );

    void_allocator allocator(segment.get_segment_manager());
    auto *test_object = segment.find_or_construct<big_object>("test_object")(big_object::key_compare(), allocator);

    string_shm key1("1qaz", allocator);
    string_shm key2("2wsx", allocator);
    vector_shm<uint8_t> value1({4, 5, 6}, allocator);
    vector_shm<uint8_t> value2({1, 2, 3}, allocator);

    test_object->emplace(key1,value1);
    test_object->emplace(key2,value2);

    auto it = test_object->find("2wsx");
    for (auto &i:it->second) {
        std::cerr << static_cast<int>(i) << std::endl;
    }
    segment.destroy_ptr(test_object);
    return 0;
}