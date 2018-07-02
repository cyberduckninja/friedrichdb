
#include <friedrichdb/in-memory/in_memory_table.hpp>
#include <iostream>


namespace friedrichdb {
    namespace in_memory {


        in_memory_table::in_memory_table(const std::string &name) : abstract_table(name) {}

        auto in_memory_table::apply(transaction trx) -> output_transaction {
            output_transaction tmp(trx);
            std::unique_lock<std::mutex> lock(mutext);
            {

                for (auto &i:trx) {
                    if (name() == i.table) {
                        switch (i.operation_) {
                            case operation_type::insert: {
                                tmp.emplace_back(create(i));
                                break;
                            }
                            case operation_type::find: {
                                tmp.emplace_back(find(i));
                                break;
                            }
                            case operation_type::upsert: {
                                tmp.emplace_back(modify(i));
                                break;
                            }
                            case operation_type::remove: {
                                tmp.emplace_back(remove(i));
                                break;
                            }
                        }
                    } else {
                        /**/  /// else
                    } /// if

                } /// for

            } /// loks

            return tmp;

        } ///apply



        output_operation in_memory_table::find(operation query_) {
            if ( query_.operation_ == operation_type::find ) {
                output_operation tmp(query_);
                auto it = storage_.find(query_.document_key);

                if (it != storage_.end()) {
                    auto result = it->second.at(query_.field_name);
                } else {

                }

                return tmp;
            } else {
                ///else
            }
        }

        output_operation in_memory_table::remove(operation query_) {
            if (query_.operation_ == operation_type::remove) {
                output_operation tmp(query_);
                storage_.erase(query_.document_key);
                return tmp;
            }
        }

        output_operation in_memory_table::create(operation query_) {
            if (query_.operation_ == operation_type::insert) {
                output_operation tmp(query_);
                auto result =  storage_.emplace(query_.document_key, document());
                if(result.second){
                    result.first->second.emplace(query_.field_name,query_.field_value);
                }
                return tmp;
            } else {
                ///else
            }

        }

        output_operation in_memory_table::modify(operation query_) {
            if (query_.operation_ == operation_type::upsert) {
                output_operation tmp(query_);
                auto it = storage_.find(query_.document_key);
                if (it == storage_.end()) {
                    auto cursor = storage_.emplace(query_.document_key, document());
                    cursor.first->second.emplace(query_.field_name, query_.field_value);
                } else {
                    it->second.emplace(query_.field_name, query_.field_value);
                }

                return tmp;
            } else {
                ///else
            }
        }

        in_memory_table::~in_memory_table() = default;


    }
}
