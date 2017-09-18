#ifndef TABLE_SCHEMA_H
#define TABLE_SCHEMA_H

#include <vector>
#include <string>
#include <initializer_list>

#include "type.hpp"

namespace friedrichdb {

    struct element final {
        element(const std::string &name, tuple::type::meta_type id_type)
                :
                name(name),
                id_type(id_type)
        {}

        ~element() = default;

        std::string name;
        tuple::type::meta_type id_type;

    };

    class schema final {
    public:

        struct __element__ final {
            __element__(const std::string &name, std::size_t id, tuple::type::meta_type id_type)
                    :
                    name(name),
                    id(id),
                    id_type(id_type)
            {}

            ~__element__() = default;

            std::string name;
            std::size_t id;
            tuple::type::meta_type id_type;

        };

        using type_type=std::vector<__element__>;

        ~schema() = default;

        schema(std::initializer_list<element> raw_schema) {
            for (const auto &i: raw_schema) {
                auto number = types.size();
                types.push_back(__element__{i.name, number, i.id_type});
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

        type_type types;
    };

}

#endif //TABLE_SCHEMA_H
