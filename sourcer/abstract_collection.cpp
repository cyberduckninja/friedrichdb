#include <friedrichdb/abstract_collection.hpp>

namespace friedrichdb {

    abstract_collection::abstract_collection(std::string name) :name_(std::move(name)){}

    const std::string &abstract_collection::name() const {
        return name_;
    }

}