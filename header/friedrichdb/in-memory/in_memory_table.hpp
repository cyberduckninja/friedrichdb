#pragma once

#include <unordered_map>
#include <string>

#include <friedrichdb/abstract_collection.hpp>
#include <friedrichdb/document/document.hpp>
#include <friedrichdb/composite_key.h>

namespace friedrichdb { namespace in_memory {

        class row final  {
            std::vector<field> row_;
        };

        using header = std::vector<std::string>;

        class in_memory_table final : public abstract_collection {
        public:
            in_memory_table(const std::string &name);
            in_memory_table();
            ~in_memory_table() override = default;
            auto apply(transaction) -> output_transaction override ;
            auto find_or_create_document(const composite_key&) -> document&;
            auto remove_document(operation) -> output_operation;

            auto find(operation)    -> output_operation;
            auto remove(operation)  -> output_operation;
            auto create(operation)  -> output_operation;
            auto upsert(operation)  -> output_operation;
            auto replace(operation) -> output_operation;

        private:
            header header_;
            std::vector<field> storage_;
        };

    }}