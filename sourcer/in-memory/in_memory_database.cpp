#include <iostream>

#include <friedrichdb/abstract_database.hpp>
#include "friedrichdb/in-memory/in_memory_database.hpp"
#include <friedrichdb/in-memory/in_memory_collection.hpp>
#include <friedrichdb/in-memory/in_memory_database.hpp>


namespace friedrichdb {
    namespace in_memory {


        in_memory_database::in_memory_database() : abstract_database(storge_t::memory) {
        }

        auto in_memory_database::apply(query&& query_) -> output_query {
            output_query tmp(query_);
            std::unique_lock<std::mutex> lock(mutex);
            {
                    for (auto &trx:query_) {
                        for (auto &j:trx) {
                            auto result =  find_collection(j.collection);

                            if(result.first){
                                result.second->apply(trx);
                            } else {
                                auto new_collection = create_collection(j.collection);
                                if(new_collection == nullptr ){
                                    std::cerr<< "-1" <<std::endl;
                                } else {
                                    new_collection->apply(trx);
                                }
                            }

                        }

                    } /// for

            } /// lock
            return tmp;
        }

        output_operation in_memory_database::remove_collection(operation) {
            return output_operation();
        }



        auto in_memory_database::find_collection(const std::string &name) -> std::pair<bool, abstract_collection *> {
            auto it = tables_.find(name);
            if (it == tables_.end()) {
                return std::make_pair(true,it->second.get());
            } else {
               return std::make_pair(false, nullptr);
            }
        }

        auto in_memory_database::create_collection(const std::string &name) -> abstract_collection * {
            auto *table = new in_memory_collection(name);
            auto current_table = tables_.emplace(name, table);
            return current_table.first->second.get();

        }


            in_memory_database::~in_memory_database() =default;
        }
    }
