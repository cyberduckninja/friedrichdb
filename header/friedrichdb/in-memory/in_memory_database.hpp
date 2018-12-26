#pragma once

#include <friedrichdb/abstract_collection.hpp>
#include <friedrichdb/query_scheduler.hpp>
#include <friedrichdb/database.hpp>

namespace friedrichdb { namespace in_memory {

        class in_memory_database final : public abstract_database {
        public:

            in_memory_database();

            ~in_memory_database();

            auto apply(query&&) -> output_query override ;

        private:
            auto remove_collection(operation)              -> output_operation;
            auto create_collection(const std::string&name) -> abstract_collection*;
            auto find_collection(const std::string&name)   -> std::pair<bool,abstract_collection*>;
            std::unordered_map<std::string, std::unique_ptr<abstract_collection>> tables_;
        };

    }
}

