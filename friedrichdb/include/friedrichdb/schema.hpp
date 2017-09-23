#ifndef TABLE_SCHEMA_H
#define TABLE_SCHEMA_H

#include <vector>
#include <string>
#include <initializer_list>

#include "type.hpp"
#include "meta_data_t.hpp"

namespace friedrichdb {

    class schema final {
    private:
        struct __element__ final {
            __element__(const std::string &name, std::size_t id, run_time_type::meta_type type);

            ~__element__() = default;

            meta_data_t type;
            std::size_t id;
        };

        using type_type = std::vector<__element__>;

    public:
        ~schema() = default;
        /// |name:type:id|name:type:id|name:type:id|
        explicit schema(std::initializer_list<meta_data_t> raw_schema);

        /// compile time check
        template <typename T>
        auto check(const T& data) const  -> bool {
            return hash == data.template hash();
        }

        auto size() const -> std::size_t;

        auto begin() -> type_type::iterator;

        auto end() -> type_type::iterator;

    private:
        type_type types;
        std::size_t hash;
    };

}

#endif //TABLE_SCHEMA_H
