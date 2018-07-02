#include <utility>

#include <friedrichdb/abstract_database.hpp>
#include <string>

namespace friedrichdb {

    storge_t abstract_database::type() const {
        return type_;
    }

    abstract_database::abstract_database(
            storge_t type
    ):
            type_(type) {

    }

}
