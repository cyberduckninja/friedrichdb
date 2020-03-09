#ifndef VIEW_T_HPP
#define VIEW_T_HPP
#include "friedrichdb/meta_data_t.hpp"
#include "friedrichdb/field_t.hpp"
#include "friedrichdb/type.hpp"

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
        }
}

#endif //VIEW_T_HPP
