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
            __element__(const std::string &name, std::size_t id, run_time_type::meta_type type)
                    :
                    id(id),
                    type(name,type)

            {}

            ~__element__() = default;

            meta_data_t type;
            std::size_t id;
        };

        using type_type = std::vector<__element__>;

    public:

        ~schema() = default;

        schema(std::initializer_list<meta_data_t> raw_schema) {
            for (const auto &i: raw_schema) {
                auto number = types.size();
                types.push_back(__element__{i.name, number, i.type});
            }
        }

        std::size_t size() const {
            return types.size();
        }

        auto begin() -> type_type::iterator {
            return types.begin();
        };

        auto end() -> type_type::iterator {
            return types.end();
        };

    private:
        type_type types;
    };

}

#endif //TABLE_SCHEMA_H
