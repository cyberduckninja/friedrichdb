#include <utility>

#include <friedrichdb/abstract_database.hpp>
#include <string>

namespace friedrichdb {

    abstract_database::storge_t abstract_database::type() const {
        return type_;
    }

    abstract_database::abstract_database(std::string name,abstract_database::storge_t type):name_(std::move(name)),type_(type) {

    }

    const std::string &abstract_database::name() const {
        return name_;
    }


}
