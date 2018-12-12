#pragma once

#include <unordered_map>
#include <string>

#include <friedrichdb/abstract_collection.hpp>
#include <friedrichdb/document.hpp>
#include <friedrichdb/composite_key.h>

namespace friedrichdb { namespace in_memory {

        class in_memory_collection final : public abstract_collection {
        public:
            in_memory_collection(const std::string &name);
            ~in_memory_collection() override;
            auto apply(transaction) -> output_transaction override ;

        private:
            document& find_or_create_document(const composite_key&);
            ///output_operation remove_document(operation);

            output_operation find(operation);
            output_operation remove(operation);
            output_operation create(operation);
            output_operation upsert(operation);
            output_operation replace(operation);

            std::unordered_map<composite_key,document> storage_;
        };
    }
}

