#ifndef DOUBLE_TT_HPP
#define DOUBLE_TT_HPP

#include "view_t.hpp"

namespace friedrichdb {
    namespace view {
///  double
        class double_tt final : public view_t {
        public:
            using view_type = compile_time_type::double_t;

            void set(double data) {
                auto tmp = std::to_string(data);
                field->push_back(tmp.data(), tmp.length());
            }

            double_tt(field_ptr field) : view_t(field) {}

            ~double_tt() = default;

        };
    }
}
#endif //PROJECT_DOUBLE_TT_HPP
