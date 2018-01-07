#ifndef ABSTRACT_TABLE_HPP
#define ABSTRACT_TABLE_HPP

#include <functional>
#include <friedrichdb/tuple_t.hpp>
#include "abstract_index.hpp"
#include "schema.hpp"

namespace friedrichdb {

    using row             = tuple_t;
    using response        = std::vector<row>;
    using where           = std::function<bool(row)>;
    using generator       = std::function<response()>;
    using where_generator = std::function<row(row)>;

    class abstract_index;

    enum class index_storage_type {
        memory = 0x00,
        persistent
    };

    struct abstract_table {

        abstract_table() = default;

        virtual ~abstract_table() = default;

        virtual response find(std::initializer_list<std::string>, where) const = 0;

        virtual bool update(where_generator) = 0;

        virtual bool erase(where) = 0;

        virtual bool insert(generator) = 0;

    protected:
        virtual bool index(const std::string &, abstract_index *) =0;

        virtual abstract_index* index(const std::string &) = 0;
        virtual abstract_index* index(const std::string &) const = 0;

    };
}
#endif //VERSIONS_ABSTRACT_DATABASE_HPP
