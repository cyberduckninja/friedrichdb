#include <friedrichdb/shared_memory/shm.hpp>

constexpr static char* name = "MySharedMemory";

int main() {
    struct shm_remove final{
        shm_remove() { boost::interprocess::shared_memory_object::remove(name); }
        ~shm_remove(){ boost::interprocess::shared_memory_object::remove(name); }
    } remover;

    boost::interprocess::managed_shared_memory segment(
            boost::interprocess::open_or_create,
            name,
            65536
    );

    

    return 0;
}