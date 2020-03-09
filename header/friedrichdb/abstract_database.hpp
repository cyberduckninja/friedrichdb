#ifndef ABSTRACT_DATABASE_HPP
#define ABSTRACT_DATABASE_HPP

#include <unordered_map>
#include "schema.hpp"

namespace friedrichdb {
    struct abstract_table;

    struct abstract_database {
        virtual abstract_table *table(const std::string &name) = 0;

        virtual abstract_table *table(const std::string &name) const = 0;

        virtual bool table(const std::string &, abstract_table *) =0;

        virtual bool table(schema&&)=0;


        enum class storge_t : uint8_t {
            memory = 0x00,
            disk,
            instance
        };

        storge_t type() const;

        explicit abstract_database(storge_t);

    private:
        storge_t type_;
    };
}
#endif //ABSTRACT_DATABASE_HPP
