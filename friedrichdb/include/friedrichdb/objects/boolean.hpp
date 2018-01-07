#ifndef BOOLEAN_HPP
#define BOOLEAN_HPP

#include "view_t.hpp"

namespace friedrichdb {

    namespace view {

        class boolean final : public view_t {
        public:
            using view_type = compile_time_type::boolean_t;

            void set(bool data) {
                auto tmp = std::to_string(data);
                field->push_back(tmp.data(), tmp.length());
            }

            boolean(field_ptr field) : view_t(field) {}

            ~boolean() = default;
        };
    }
}
#endif //PROJECT_BOOLEAN_HPP
