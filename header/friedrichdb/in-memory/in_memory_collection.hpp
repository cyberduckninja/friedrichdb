#pragma once

#include <unordered_map>
#include <string>

#include <friedrichdb/abstract_collection.hpp>
#include <friedrichdb/document/document.hpp>
#include <friedrichdb/composite_key.h>

namespace friedrichdb { namespace in_memory {

        class in_memory_collection final : public abstract_collection {
        public:
            in_memory_collection(const std::string &name);
            ~in_memory_collection() override = default;
            auto apply(transaction) -> output_transaction override ;

        private:
            auto find_or_create_document(const composite_key&) -> document&;
            auto remove_document(operation) -> output_operation;

            auto find(operation)    -> output_operation;
            auto remove(operation)  -> output_operation;
            auto create(operation)  -> output_operation;
            auto upsert(operation)  -> output_operation;
            auto replace(operation) -> output_operation;

            std::unordered_map<composite_key,document> storage_;
        };
    }
}

