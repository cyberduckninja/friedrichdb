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

        struct base_field_t {
            base_field_t() = default;
            base_field_t(const base_field_t&)= delete;
            base_field_t&operator()(const base_field_t&)= delete;
            base_field_t(const std::string &name, type::meta_type type) : name(name), type(type),body(new base) {}

            std::string name;
            type::meta_type type;
            std::unique_ptr<base> body;

            virtual ~base_field_t() = default;
        };

        ///   field_t -> { id, name, field_1 }
        struct field_t final : public base_field_t {
            field_t() = default;
            field_t(const field_t&)= delete;
            field_t&operator()(const field_t&)= delete;
            field_t(const std::string &name, size_t id, type::meta_type type) : id(id), base_field_t(name, type) {}
            std::size_t id;
            ~field_t() = default;
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
                    t.emplace_back(std::make_shared<field_t>(i.name, size, i.type));
                }
            }

            std::shared_ptr<field_t> operator[](position_key key) {
                //        strat <position <= stop
                //assert(t.size() >= index.position);
                //assert(index.position<1 );
                auto tmp = t[key.key];
                assert(tmp->type == key.type);
                return tmp;
            }

            std::shared_ptr<field_t> operator[](string_key key) {
                //        strat <position <= stop
                //assert(t.size() >= index.position);
                //assert(index.position<1 );
                auto position = index_of_name[key.key];
                auto tmp = t[position];
                assert(tmp->type == key.type);
                return tmp;
            }

            ~tuple() = default;

        private:
            std::unordered_map<std::string, offest> index_of_name;
            std::vector<std::shared_ptr<field_t>> t;
        };

    }

    using tuple::string_key;
    using tuple::position_key;

}

#endif //PROJECT_TUPLE_HPP
