#ifndef ABSTRACT_TABLE_HPP
#define ABSTRACT_TABLE_HPP


#include <mutex>
#include <condition_variable>
#include <functional>
#include <friedrichdb/abstract_index.hpp>
#include <friedrichdb/query.hpp>
#include <friedrichdb/query.hpp>


namespace friedrichdb {

    class abstract_index;

    enum class index_storage_type {
        memory = 0x00,
        persistent
    };

    struct abstract_table {

        abstract_table() = default;

        virtual ~abstract_table() = default;

        virtual auto exec(query) -> query_result = 0;

    protected:
        std::mutex  mutext;
        virtual auto index(const std::string &, abstract_index *) -> bool =0;
        virtual auto index(const std::string &)                   -> abstract_index* = 0;
        virtual auto index(const std::string &) const             -> abstract_index* = 0;

    };
}
#endif //VERSIONS_ABSTRACT_DATABASE_HPP
