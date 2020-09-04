#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <nlohmann/json.hpp>


using namespace nlohmann;
namespace py = pybind11;


class context {

};

json to_json_impl(const py::handle &obj) {
    if (obj.is_none()) {
        return nullptr;
    } if (py::isinstance<py::bool_>(obj)) {
        return obj.cast<bool>();
    } if (py::isinstance<py::int_>(obj)) {
        return obj.cast<long>();
    } if (py::isinstance<py::float_>(obj)) {
        return obj.cast<double>();
    } if (py::isinstance<py::str>(obj)) {
        return obj.cast<std::string>();
    } if (py::isinstance<py::tuple>(obj) || py::isinstance<py::list>(obj)) {
        auto out = json::array();
        for (const py::handle &value : obj) {
            out.push_back(to_json_impl(value));
        }
        return out;
    } if (py::isinstance<py::dict>(obj)) {
        auto out = json::object();
        for (const py::handle &key : obj) {
            out[py::str(key).cast<std::string>()] = to_json_impl(obj[key]);
        }
        return out;
    }
    throw std::runtime_error("to_json not implemented for this type_ of object: " + obj.cast<std::string>());
}

py::object from_json_impl(const json &j) {
    if (j.is_null()) {
        return py::none();
    } else if (j.is_boolean()) {
        return py::bool_(j.get<bool>());
    } else if (j.is_number()) {
        auto number = j.get<double>();
        if (number == std::floor(number)) {
            return py::int_(j.get<long>());
        } else {
            return py::float_(number);
        }
    } else if (j.is_string()) {
        return py::str(j.get<std::string>());
    } else if (j.is_array()) {
        py::list obj;
        for (const auto &el : j) {
            obj.attr("append")(from_json_impl(el));
        }
        return obj;
    } else { // Object
        py::dict obj;
        for (json::const_iterator it = j.cbegin(); it != j.cend(); ++it) {
            obj[py::str(it.key())] = from_json_impl(it.value());
        }
        return obj;
    }
}


template <class Serialization>
class pipe_lined_ds;

template <class Serialization>
class data_set {
public:
    data_set(pybind11::object& collections, context* ctx = nullptr ):collection_(collections) {

    }

    auto id() { return partitioner; }

    data_set<Serialization>* map( py::function f, bool preservesPartitioning=false){


    }

    data_set<Serialization>* map_partitions_with_index( py::function f, bool preservesPartitioning=false){
        return new  pipe_lined_ds<Serialization>(this,f,preservesPartitioning);
    }

private:


    py::object collection_;
    std::vector<json> data_set_;
    bool is_cached;
    bool is_checkpointed;
    context ctx;
    ///_jrdd_deserializer = jrdd_deserializer
    std::size_t _id;
    std::size_t partitioner;
};

template <class Serialization>
class pipe_lined_ds final : public data_set<Serialization> {
public:
    using data_set_current = data_set<Serialization>;

    pipe_lined_ds(data_set_current* ptr,py::function func, bool preservesPartitioning=false){

    }
};



int main() {

    return 0;
}