
#include <friedrichdb/in-memory/in_memory_collection.hpp>


namespace friedrichdb {
    namespace in_memory {


        in_memory_collection::in_memory_collection(const std::string &name) : abstract_collection(name) {}

        auto in_memory_collection::apply(transaction trx) -> output_transaction {
            output_transaction tmp(trx);
            std::unique_lock<std::mutex> lock(mutext);
            {

                for (auto &i:trx) {
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
                            tmp.emplace_back(upsert(i));
                            break;
                        }
                        case operation_type::remove: {
                            tmp.emplace_back(remove(i));
                            break;
                        }

                        case operation_type::replace: {
                            tmp.emplace_back(replace(i));
                            break;
                        }
                    }

                } /// for

            } /// loks

            return tmp;

        } ///apply



        output_operation in_memory_collection::find(operation query_) {
            output_operation tmp(query_);

            find_or_create_document(query_.embedded_document_.document_id);

            return tmp;

        }

        output_operation in_memory_collection::remove(operation query_) {
            output_operation tmp(query_);
            storage_.erase(query_.embedded_document_.document_id);
            return tmp;
        }

        output_operation in_memory_collection::create(operation query_) {
            output_operation tmp(query_);
            auto result = storage_.emplace(query_.embedded_document_.document_id, document());
            if (result.second) {
                for (auto &&i:query_.embedded_document_.fields) {
                    result.first->second.emplace(i.key, i.value);
                }
            }
            return tmp;

        }

        output_operation in_memory_collection::upsert(operation query_) {
            output_operation tmp(query_);
            auto& document = find_or_create_document(query_.embedded_document_.document_id);
            for(auto&&i:query_.embedded_document_.fields){
                document.emplace(i.key,i.value);
            }

            return tmp;

        }

        output_operation in_memory_collection::replace(operation query_) {
            output_operation tmp(query_);

        }

        auto in_memory_collection::find_or_create_document(const composite_key&key) -> document& {
            auto it = storage_.find(key);
            if (it == storage_.end()) {
                auto cursor = storage_.emplace(key, document());
                return cursor.first->second;
            } else {
                return it->second;
            }
        }

        in_memory_collection::~in_memory_collection() = default;


    }
}
