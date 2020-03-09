#ifndef TUPLE_HPP
#define TUPLE_HPP

#include <vector>
#include <string>
#include <unordered_map>
#include <friedrichdb/meta_data_t.hpp>
#include <cassert>
#include "type.hpp"
#include "field_t.hpp"
#include "friedrichdb/objects/view_t.hpp"

namespace friedrichdb {

        using offest = std::size_t;

        ///   complex_key
        struct position_key final {
            const std::size_t key;
            const run_time_type::meta_type type;
        };

        struct string_key final {
            const std::string key;
            const run_time_type::meta_type type;
        };

        ///   <field_t1, field_t2, field_t3, ..., field_tN >
        class tuple_t final {
        public:
            tuple_t() = default;
            tuple_t(const tuple_t&) = delete;
            tuple_t&operator=(const tuple_t&) = delete;
            tuple_t(tuple_t&&) = default;
            tuple_t&operator=(tuple_t&&) = default;
            ~tuple_t() = default;

            /// |name:type:id|name:type:id|name:type:id|
            tuple_t(std::initializer_list<meta_data_t> init_list);

            /// compile time check
            template <typename T>
            auto get(const std::string& key) -> T {
                auto position = index_of_name[key];
                auto meta = meta_info[position];
                typename T::view_type view;
                assert(static_cast<uint8_t >(meta.type.id) == view.id_);
                T tmp{t[position]};
                return tmp;
            }

            /// compile time check
            template <typename T>
            auto get(std::size_t key) -> T {
                assert(key <= t.size());
                assert(key >= 0);
                auto meta = meta_info[key];
                typename T::view_type view;
                assert(static_cast<uint8_t >(meta.type.id) == view.id_);
                T tmp{t[key]};
                return tmp;
            }

            /// run time check
            auto get(string_key key) -> field_ptr;
            /// run time check
            auto get(position_key key) -> field_ptr;

            auto hash() const -> std::size_t;

        private:
            std::unordered_map<std::string, offest> index_of_name;
            std::vector<meta_data_t> meta_info;
            std::vector<field_ptr> t;
            std::size_t hash_;
        };

        template<typename T,std::size_t Index>
        auto get(tuple_t& tuple) -> T {
            return tuple.get<T>(Index);
        };

        template<typename T,std::size_t Size>
        auto get(tuple_t& tuple,const char(&DATA)[Size]) -> T {
            return tuple.get<T>({DATA,Size-1});
        };

}

#endif //TUPLE_HPP
