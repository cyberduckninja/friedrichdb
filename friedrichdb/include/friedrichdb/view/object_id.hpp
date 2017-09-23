#ifndef PROJECT_OBJECT_ID_HPP
#define PROJECT_OBJECT_ID_HPP

#include "view_t.hpp"

namespace friedrichdb {

    namespace view {

        class object_id final : public view_t{
        public:
            object_id(field_ptr field) : view_t(field) {}
            void set(double data) {}
            ~object_id()=default;
        };

    }
}
#endif //PROJECT_OBJECT_ID_HPP
