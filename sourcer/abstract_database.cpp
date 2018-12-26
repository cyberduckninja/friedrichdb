#include <utility>

#include <friedrichdb/abstract_database.hpp>
#include <string>

namespace friedrichdb {

    storage_type abstract_database::type() const {
        return type_;
    }

    abstract_database::abstract_database(
            storage_type type
    ):
            type_(type) {

    }

}
