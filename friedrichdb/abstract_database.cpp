#include <friedrichdb/abstract_database.hpp>
namespace friedrichdb {

    abstract_database::storge_t abstract_database::type() const {
        return abstract_database::storge_t::instance;
    }

    abstract_database::abstract_database(abstract_database::storge_t type):type_(type) {

    }


}
