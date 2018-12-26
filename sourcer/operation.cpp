#include <friedrichdb/operation.hpp>

namespace friedrichdb {

    std::string to_string(friedrichdb::operation_type type) {
        switch (type) {

            case friedrichdb::operation_type::insert:
                return "insert";
            case friedrichdb::operation_type::find:
                return "find";
            case friedrichdb::operation_type::upsert:
                return "upsert";
            case friedrichdb::operation_type::remove:
                return "remove";
            default:
                throw std::exception();
        }
    }

    operation_type from_string(const std::string& type) {

        switch (*type.begin()) {
            case 'i':
                return friedrichdb::operation_type::insert;
            case 'f':
                return friedrichdb::operation_type::find;
            case 'u':
                return friedrichdb::operation_type::upsert;
            case 'r':
                return friedrichdb::operation_type::remove;

            default:
                throw std::exception();
        }

    }

    binary_data operation::serialization_json() const {

    }

    void operation::deserialization_json(binary_data) {

    }

    void output_operation::deserialization_json(std::string) {

    }

    std::string output_operation::serialization_json() const {

    }

    output_operation::output_operation(const operation &operation_) {
        this->query_id = operation_.query_id;
        this->transaction_id = operation_.transaction_id;
        this->id = operation_.id;
        this->operation_ = operation_.operation_ ;
        this->collection = operation_.collection;
        this->embedded_document_ = operation_.flat_document_;

    }
}
