
#include <string>

#include <friedrichdb/database.hpp>
#include <friedrichdb/query.hpp>
#include <cassert>

namespace friedrichdb {


    database::database(const std::string &name, abstract_database*memory) : name_(name), memory(memory) {
        assert(memory->type() == storage_type::memory);
    }

    database::database(const std::string &name,abstract_database*memory, abstract_database*file) : name_(name), memory(memory), file(file) {
        assert(memory->type() == storage_type::memory);
        assert(file->type() == storage_type::disk);
    }

    auto database::name() -> const std::string & {
        return name_;
    }


}