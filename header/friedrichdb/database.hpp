#ifndef DATABASE_HPP
#define DATABASE_HPP

#include <vector>
#include <functional>
#include <cassert>
#include <memory>

#include <friedrichdb/journal.hpp>
#include <friedrichdb/abstract_database.hpp>
#include <friedrichdb/pool.hpp>

namespace friedrichdb {

    class database final : public abstract_database {
    public:
        database(const std::string&,abstract_database *memory, abstract_database *file);

        ~database() = default;

        auto apply(query&&) -> output_query override;

    private:
        journal journal_;
        std::unique_ptr<abstract_database> memory;
        std::unique_ptr<abstract_database> file;
    };
}
#endif //FRIEDRICHDB_DATABASE_HPP
