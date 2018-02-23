#include "friedrichdb/database.hpp"
namespace friedrichdb {

    bool database::table(const std::string &name, abstract_table *ptr) {
        return memory->table(name,ptr);
    }

    abstract_table *database::table(const std::string &name) {
        return memory->table(name);
    }

    abstract_table *database::table(const std::string &name) const {
        return memory->table(name);
    }

    abstract_database::storge_t database::type() const {
        return memory->type();
    }

    bool database::table(schema &&) {
        return false;
    }

    database::database(abstract_database *memory, abstract_database *file) :abstract_database(storge_t::instance) {
        assert(memory->type() != storge_t::memory);
        assert(file->type() != storge_t::disk);
        this->memory.reset(memory);
        this->file.reset(file);
    }

}