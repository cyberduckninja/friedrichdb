#ifndef TUPLE_HPP
#define TUPLE_HPP

#include <vector>
#include <string>
#include <unordered_map>
#include <cassert>
#include <friedrichdb/tuple/meta_data_t.hpp>
#include "friedrichdb/tuple/ordering.h"
#include "friedrichdb/type.hpp"

namespace friedrichdb {

    namespace tuple {

        using offest = std::size_t;
        using byte   = std::uint8_t;

        ///   complex_key
        struct position_key final {
            const std::size_t key;
            const type::meta_type type;
        };

        struct string_key final {
            const std::string key;
            const type::meta_type type;
        };

        ///   <field_t1, field_t2, field_t3, ..., field_tN >
        class tuple final {
        private:

            class field_t final : public implement::ordered<field_t> {
            public:
                field_t() = default;
                ~field_t() = default;

                void set(const char *data, std::size_t size);

            private:
                std::vector<byte> data_;
            };

            using field_ptr = std::shared_ptr<field_t>;

        public:

            tuple() = delete;
            tuple(const tuple&) = delete;
            tuple&operator=(const tuple&) = delete;
            tuple(tuple&&) = default;
            tuple&operator=(tuple&&) = default;
            ~tuple() = default;

            tuple(std::initializer_list<meta_data_t> init_list);

            std::shared_ptr<field_t> operator[](position_key key);

            std::shared_ptr<field_t> operator[](string_key key);

        private:
            std::unordered_map<std::string, offest> index_of_name;
            std::vector<meta_data_t> meta_info;
            std::vector<field_ptr> t;
        };
    }

    using tuple::string_key;
    using tuple::position_key;

}

#endif //TUPLE_HPP
