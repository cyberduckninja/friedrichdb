#ifndef PROJECT_OBJECT_ID_HPP
#define PROJECT_OBJECT_ID_HPP

#include <friedrichdb/data_types/object_id.hpp>
#include "view_t.hpp"

namespace friedrichdb {

    namespace view {

        class object_id final : public view_t{
        public:
            object_id(field_ptr field) : view_t(field) {}

            void set(const data_types::object_id& data) {
                field->push_back(data.to_string().data(),data.to_string().length());
            }

            data_types::object_id get() const {
                return data_types::object_id(static_cast<const char*>(field->data()));
            }

            ~object_id()=default;
        };

    }
}
#endif //PROJECT_OBJECT_ID_HPP
