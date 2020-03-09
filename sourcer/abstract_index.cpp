
#include "friedrichdb/abstract_index.hpp"

namespace friedrichdb {


    const std::string &abstract_index::name() const {
        return name_;
    }

    abstract_index::abstract_index(const std::string &name, index_type type) : name_(name) {

    }

    index_type abstract_index::type() const {
        return type_;
    }


}

