#ifndef TUPLE_HPP
#define TUPLE_HPP

#include <vector>
#include <string>
#include <unordered_map>
#include <cassert>
#include "friedrichdb/tuple/ordering.h"
#include "friedrichdb/type.hpp"

namespace friedrichdb {

    namespace tuple {

        using offest = std::size_t;

        struct field_type final {
            const std::string name;
            const type::meta_type type;
        };

        ///   complex_key
        struct position_key final {
            const std::size_t key;
            const type::meta_type type;
        };

        struct string_key final {
            const std::string key;
            const type::meta_type type;
        };

        ///   segment -> {ptr * storage tuple ;   }
        ///   copy semantic
        struct base : public implement::ordered<base> {
            base() = default;

            void set(const char *data, std::size_t size) {
                data_.resize(size);
                for (std::size_t i = 0; i < size; ++i) {
                    data_[i] = data[i];
                }
            }

            std::vector<char> data_;

            virtual ~base() = default;
        };

        struct meta_data_field_t final {

            meta_data_field_t() = default;
            meta_data_field_t(const meta_data_field_t&)= default;
            meta_data_field_t&operator=(const meta_data_field_t&)= default;
            ~meta_data_field_t() = default;

            meta_data_field_t(const std::string &name, type::meta_type type) : name(name), type(type)  {}
            std::string name;
            type::meta_type type;
        };

        ///   <field_t1, field_t2, field_t3, ..., field_tN >
        class tuple final {
        public:
            tuple() = default;

            explicit tuple(std::initializer_list<field_type> init_list) {
                t.reserve(init_list.size());
                for (auto &i:init_list) {
                    auto size = t.size();
                    index_of_name.emplace(i.name, size);
                    meta_info.emplace_back(meta_data_field_t{i.name, i.type});
                    t.emplace_back(std::move(std::make_shared<base>()));
                }
            }

            std::shared_ptr<base> operator[](position_key key) {
                assert( key.key <= t.size() );
                assert( key.key >= 0 );
                auto meta = meta_info[key.key];
                assert(meta.type == key.type);
                auto tmp = t[key.key];
                return tmp;
            }

            std::shared_ptr<base> operator[](string_key key) {
                auto position = index_of_name[key.key];
                auto meta = meta_info[position];
                assert(meta.type == key.type);
                auto tmp = t[position];
                return tmp;
            }

            ~tuple() = default;

        private:
            std::unordered_map<std::string, offest> index_of_name;
            std::vector<meta_data_field_t> meta_info;
            std::vector<std::shared_ptr<base>> t;
        };
    }

    using tuple::string_key;
    using tuple::position_key;

}

#endif //PROJECT_TUPLE_HPP
