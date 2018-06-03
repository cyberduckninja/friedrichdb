#pragma once

#include <friedrichdb/abstract_table.hpp>
#include <unordered_map>
#include "part_manager.hpp"

namespace friedrichdb {
    namespace in_memory {

        class table : public abstract_table {
        public:



        protected:
            abstract_index* index(const std::string &);
            abstract_index* index(const std::string &) const;
            auto index(const std::string &name, abstract_index *index) -> bool ;
        private:
            std::unordered_map<std::string, std::unique_ptr<abstract_index>> index_manager;
            part_manager pm;
        };
    }
}

