#ifndef DATABASE_HPP
#define DATABASE_HPP

#include <vector>
#include <functional>
#include <cassert>

#include "abstract_database.hpp"

namespace friedrichdb {

    class database final : public abstract_database {
    public:
        database(abstract_database *memory, abstract_database *file);

        ~database() = default;

        abstract_table *table(const std::string &name) const ;

        abstract_table *table(const std::string &name);

        bool table(const std::string &, abstract_table *);

        bool table(schema&&);

    private:
        storge_t type() const;
        std::unique_ptr<abstract_database> memory;
        std::unique_ptr<abstract_database> file;
    };
}
#endif //FRIEDRICHDB_DATABASE_HPP
