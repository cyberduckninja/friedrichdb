#ifndef ABSTRACT_INDEX_HPP
#define ABSTRACT_INDEX_HPP


#include <cstdint>
#include <cstddef>
#include "abstract_table.hpp"

namespace friedrichdb {

        struct address final {
            std::size_t part_number;
            std::size_t number;
        };

        enum class index_type : uint8_t {
            abstract_index = 0x00,
            hash_index,
            unique_hash_index
        };

        class abstract_index {
        public:
            abstract_index():type_(index_type::abstract_index){}
            explicit abstract_index(const std::string& name,index_type);
            const std::string& name() const;
            index_type type() const;

            virtual ~abstract_index() = default;

        private:
            std::string name_;
            index_type type_;
        };
}
#endif //ABSTRACT_INDEX_HPP
