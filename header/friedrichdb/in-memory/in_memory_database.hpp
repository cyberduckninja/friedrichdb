#ifndef TABLE_H
#define TABLE_H

#include "friedrichdb/abstract_table.hpp"
#include <functional>
#include "friedrichdb/tuple_t.hpp"
#include "friedrichdb/schema.hpp"
#include "friedrichdb/data_types/object_id.hpp"
#include "friedrichdb/composite_key.hpp"
#include "friedrichdb/abstract_index.hpp"

namespace friedrichdb {
    namespace in_memory {
        class in_memory_database final : public abstract_database {
        public:

            in_memory_database();

            ~in_memory_database();

            abstract_table *table(const std::string &name);

            abstract_table *table(const std::string &name) const;

            bool table(const std::string &, abstract_table *);

            bool table(schema &&);

        private:
            std::unordered_map<std::string, std::unique_ptr<abstract_table>> tables_;
        };

    }
}

#endif //TABLE_TABLE_H
