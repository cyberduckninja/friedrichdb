#include <friedrichdb/document.hpp>

namespace friedrichdb {


        std::string document::serialization_json() const {

        }

        void document::deserialization_json(binary_data) {

        }

    field::field(const std::string &key, const std::string &value) : key(key), value(value) {}
}