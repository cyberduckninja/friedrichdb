#include <iostream>

#include <friedrichdb/abstract_database.hpp>
#include "friedrichdb/in-memory/in_memory_database.hpp"
#include <friedrichdb/in-memory/in_memory_table.hpp>


namespace friedrichdb {
    namespace in_memory {


        in_memory_database::in_memory_database() : abstract_database("memory", abstract_database::storge_t::memory) {
        }

        auto in_memory_database::apply(query&& query_) -> output_query {
            output_query tmp;
            std::unique_lock<std::mutex> lock(mutex);
            {

                if (name() == query_.database) {
                    for (auto &trx:query_) {
                        for (auto &j:trx) {
                            auto it = tables_.find(j.table);
                            if (it == tables_.end()) {
                                auto *table = new in_memory_table(j.table);
                                auto current_table = tables_.emplace(j.table, table);
                                tmp.emplace_back(current_table.first->second->apply(trx));
                            } else {
                                tmp.emplace_back(it->second->apply(trx));
                            }
                        }

                    } /// for

                } /// lock


            } /// apply
            return tmp;
        }

            in_memory_database::~in_memory_database() =default;
        }
    }
