#ifndef FRIEDRICHDB_DATABASE_HPP
#define FRIEDRICHDB_DATABASE_HPP

#include <vector>
#include <functional>
#include <cassert>

#include "abstract_database.hpp"

namespace friedrichdb {

    class database final : public abstract_database {
    public:
        template<typename MEMORY, typename FILE>
        database(MEMORY *memory, FILE *file):abstract_database(storge_t::instance) {
            assert(memory->type()==storge_t::memory);
            assert(file->type()==storge_t::disk);
            this->memory.reset(memory);
            this->file.reset(file);
        }

        ~database() = default;

        /// iterator ?
        response find(where) const override;

        bool update(where_generator) override;

        bool erase(where) override;

        bool insert(generator) override;

    private:
        std::unique_ptr<abstract_database> memory;
        std::unique_ptr<abstract_database> file;
    };
}
#endif //FRIEDRICHDB_DATABASE_HPP
