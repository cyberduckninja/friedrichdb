#include <pybind11/pybind11.h>

#include "wrapper/wrapper_client.hpp"
#include "wrapper/wrapper_database.hpp"
#include "wrapper/wrapper_collection.hpp"
#include "wrapper/wrapper_document.hpp"

// The bug related to the use of RTTI by the pybind11 library has been fixed: a
// declaration should be in each translation unit.
PYBIND11_DECLARE_HOLDER_TYPE(T, boost::intrusive_ptr<T>)


PYBIND11_MODULE(friedrich_db, m) {

    py::class_<wrapper_client>(m, "Client")
            .def(py::init<>())
            .def("__getitem__",&wrapper_client::create)
            .def("database_names",&wrapper_client::database_names)
            ;

    py::class_<wrapper_database,boost::intrusive_ptr<wrapper_database>>(m, "DataBase")
            .def(py::init<friedrichdb::core::database_t*>())
            .def("collection_names",&wrapper_database::collection_names)
            .def("__getitem__",&wrapper_database::create)
            ;

    py::class_<wrapper_collection,boost::intrusive_ptr<wrapper_collection>>(m, "Collection")
            .def(py::init<friedrichdb::core::collection_t*>())
            .def("insert",&wrapper_collection::insert)
            .def("insert_many",&wrapper_collection::insert_many)
            .def("get",&wrapper_collection::get, py::arg("cond") = py::none(),py::arg("doc_id")= py::none())
            .def("search ",&wrapper_collection::search, py::arg("cond"))
            .def("all ",&wrapper_collection::all)
            .def("update",&wrapper_collection::update,py::arg("fields"),py::arg("cond"))
            .def("remove",&wrapper_collection::remove,py::arg("cond"))
            .def("drop",&wrapper_collection::drop)
            .def("__len__", &wrapper_collection::size)
            ;

    py::class_<wrapper_document,boost::intrusive_ptr<wrapper_document>>(m, "Document")
            .def(py::init<friedrichdb::core::document_t*>())
            .def("__repr__",&wrapper_document::print)
            .def("__getitem__",&wrapper_document::get)
            .def("get",&wrapper_document::get)
            ;
}