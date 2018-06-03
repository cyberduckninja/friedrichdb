#ifndef DATABASE_HPP
#define DATABASE_HPP

#include <vector>
#include <functional>
#include <cassert>

#include <friedrichdb/abstract_database.hpp>

namespace friedrichdb {

    class database final : public abstract_database {
    public:
        database(abstract_database *memory, abstract_database *file);

        ~database() = default;

        auto table(const std::string &name) const         -> abstract_table *;

        auto table(const std::string &name)               -> abstract_table *;

        auto table(const std::string &, abstract_table *) -> bool;

    private:
        storge_t type() const;

        std::unique_ptr<abstract_database> memory;
        std::unique_ptr<abstract_database> file;
    };
}
#endif //FRIEDRICHDB_DATABASE_HPP
