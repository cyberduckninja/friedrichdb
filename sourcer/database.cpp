
#include <string>

#include <friedrichdb/database.hpp>
#include <friedrichdb/query.hpp>
#include <cassert>

namespace friedrichdb {


    database::database(const std::string &name, abstract_database*memory) : name(name), memory(memory) {
        assert(memory->type() == storge_t::memory);
    }

    database::database(const std::string &name,abstract_database*memory, abstract_database*file) : name(name), memory(memory), file(file) {
        assert(memory->type() == storge_t::memory);
        assert(file->type() == storge_t::disk);
    }


}