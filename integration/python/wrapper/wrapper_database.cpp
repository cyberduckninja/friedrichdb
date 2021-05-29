#include "wrapper_database.hpp"



wrapper_database::wrapper_database(wrapper_database::pointer ptr) :ptr_(ptr) {}

wrapper_database::~wrapper_database() {
    ptr_.release();
}


auto wrapper_database::collection_names() -> py::list {
    py::list tmp;
    for (auto &i:*ptr_) {
        tmp.append(i.first);
    }
    return tmp;
}

void wrapper_database::drop_collection(const std::string &name) {
    ptr_->drop(name);
}

wrapper_collection_ptr wrapper_database::create(const std::string &name) {
    return wrapper_collection_ptr(new wrapper_collection( ptr_->create(name)));
}