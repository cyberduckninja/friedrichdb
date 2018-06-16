#pragma once

#include <unordered_map>
#include <string>

#include <friedrichdb/abstract_table.hpp>
#include <friedrichdb/in-memory/document.hpp>
#include <friedrichdb/in-memory/composite_key.h>

namespace friedrichdb {
    namespace in_memory {

        class in_memory_table final : public abstract_table {
        public:
            in_memory_table(const std::string &name);
            ~in_memory_table() override;
            auto apply(transaction_t) -> output_transaction override ;

        private:
            output_operation find(operation);
            output_operation remove(operation);
            output_operation create(operation);
            output_operation modify(operation);
            std::unordered_map<composite_key,document> storage_;
        };
    }
}

