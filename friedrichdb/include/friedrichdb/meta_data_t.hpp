#ifndef PROJECT_FIELD_T_HPP
#define PROJECT_FIELD_T_HPP

#include <string>
#include "type.hpp"

namespace friedrichdb {

        struct meta_data_t final {

            meta_data_t(const std::string &name,std::size_t id, const run_time_type::meta_type &type)
                    :
                    name(name),
                    id(id),
                    type(type)
            {}

            meta_data_t(const std::string &name, const run_time_type::meta_type &type)
                    :
                    name(name),
                    type(type)
            {}

            ~meta_data_t()= default;
            std::string name;
            run_time_type::meta_type type;
            std::size_t id;

        };
}
#endif //PROJECT_FIELD_T_HPP
