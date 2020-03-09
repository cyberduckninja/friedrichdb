#ifndef POSITIVE_INTEGER_HPP
#define POSITIVE_INTEGER_HPP

#include "view_t.hpp"

namespace friedrichdb {

    namespace view {

        class positive_integer final : public view_t {
        public:
            using view_type = compile_time_type::positive_integer_t;

            void set(int data) {
                auto tmp = std::to_string(data);
                field->push_back(tmp.data(), tmp.length());
            }

            positive_integer(field_ptr field) : view_t(field) {}

            ~positive_integer() = default;
        };

    }
}
#endif //POSITIVE_INTEGER_HPP
