#ifndef PROJECT_TABLE_HPP
#define PROJECT_TABLE_HPP

#include <friedrichdb/abstract_table.hpp>
#include <friedrichdb/schema.hpp>
#include "part_manager.hpp"

namespace friedrichdb {
    namespace in_memory {

        class table : public abstract_table {
        public:

            table(schema &&current_schema);

            response find(std::initializer_list<std::string>, where) const override;

            bool update(where_generator) override;

            bool erase(where) override;

            bool insert(generator) override;

        protected:
            abstract_index* index(const std::string &);
            abstract_index* index(const std::string &) const;
            auto index(const std::string &name, abstract_index *index) -> bool ;
        private:
            schema current_schema;
            std::unordered_map<std::string, std::unique_ptr<abstract_index>> index_manager;
            part_manager pm;
        };
    }
}
#endif //PROJECT_TABLE_HPP
