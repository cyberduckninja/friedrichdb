#ifndef VIEW_HPP
#define VIEW_HPP

#include "meta_data_t.hpp"
#include "field_t.hpp"
#include "type.hpp"

namespace friedrichdb {

    namespace view {

        class view_t {
        public:
            view_t() = default;

            view_t(const view_t &) = default;

            view_t &operator=(const view_t &)= default;

            view_t(view_t &&) = default;

            view_t &operator=(view_t &&)= default;

            view_t(field_ptr field) : field(field) {}

            virtual ~view_t() = default;

        protected:
            field_ptr field;
        };

        ///  double
        class double_tt final : public view::view_t {
        public:
            using view_type = compile_time_type::double_t;

            void set(double data) {
                auto tmp = std::to_string(data);
                field->push_back(tmp.data(), tmp.length());
            }

            double_tt(field_ptr field) : view_t(field) {}

            ~double_tt() = default;

        };

        class boolean final : public view::view_t {
        public:
            using view_type = compile_time_type::boolean_t;

            void set(bool data) {
                auto tmp = std::to_string(data);
                field->push_back(tmp.data(), tmp.length());
            }

            boolean(field_ptr field) : view_t(field) {}

            ~boolean() = default;
        };

        class positive_integer final : public view::view_t {
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
#endif //VIEW_HPP
