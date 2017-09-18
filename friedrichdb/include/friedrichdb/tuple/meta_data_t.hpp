#ifndef PROJECT_FIELD_T_HPP
#define PROJECT_FIELD_T_HPP

#include <string>
#include "friedrichdb/type.hpp"

namespace friedrichdb {

    namespace tuple {

        struct meta_data_t final {

            meta_data_t(const std::string &name, const type::meta_type &type)
                    :
                    name(name),
                    type(type)
            {}

            const std::string name;
            const type::meta_type type;

        };
    }
}
#endif //PROJECT_FIELD_T_HPP
