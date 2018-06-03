
#include <friedrichdb/abstract_database.hpp>
#include "friedrichdb/in-memory/in_memory_database.hpp"
#include <friedrichdb/in-memory/table.hpp>
#include <iostream>

namespace friedrichdb {
    namespace in_memory {
        abstract_table *in_memory_database::table(const std::string &name) {
            abstract_table *tmp = nullptr;
            auto it = tables_.find(name);
            if (it == tables_.end()) {
                tmp = nullptr;
            } else {
                tmp = it->second.get();
            }


            return tmp;
        }

        abstract_table *in_memory_database::table(const std::string &name) const {
            abstract_table *tmp = nullptr;
            auto it = tables_.find(name);
            if (it == tables_.end()) {
                tmp = nullptr;
            } else {
                tmp = it->second.get();
            }

            return tmp;
        }

        bool in_memory_database::table(const std::string &name, abstract_table *ptr) {
            auto it = tables_.emplace(name, ptr);
            return it.second;
        }

        in_memory_database::in_memory_database() : abstract_database(abstract_database::storge_t::memory) {
        }

        in_memory_database::~in_memory_database() = default;
    }
}
