#ifndef UNIQUE_HASH_INDEX_HPP
#define UNIQUE_HASH_INDEX_HPP

#include "friedrichdb/abstract_index.hpp"
#include <unordered_map>

namespace friedrichdb {
    namespace index {

        class hash_index final : abstract_index {
        public:
            using index_t = std::unordered_multimap<std::size_t, address>;
            using index_iterator = index_t::iterator;
            using const_index_iterator = index_t::const_iterator;
        public:
            hash_index() : abstract_index(index_type::hash_index) {}
            std::vector<address> find(where) override {

            }


            ~hash_index() = default;

        private:
            std::unordered_multimap<std::size_t, address> index;
        };

    }
}

#endif
