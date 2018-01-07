#ifndef UNIQUE_HASH_INDEX_HPP
#define UNIQUE_HASH_INDEX_HPP

#include "friedrichdb/abstract_index.hpp"
#include <unordered_map>

namespace friedrichdb {
    namespace index {

        class unique_hash_index final : abstract_index {
        public:
            unique_hash_index() : abstract_index(index_type::unique_hash_index) {}
             std::vector<address> find(where) override {

             }

            ~hash_index() = default;
            /*
            std::size_t hash() const {

            };
            */
        private:
            std::unordered_map<std::size_t,address> index;
        };

    }
}

#endif
