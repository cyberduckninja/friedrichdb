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

    operation::operation(operation_type operation_, const std::string &table, const std::string &document_key,
                         const std::string &field_name, const std::string &field_value) :
            operation_(operation_),
            table(table),
            document_key(document_key),
            field_name(field_name),
            field_value(field_value) {

    }

    operation::operation(operation_type operation_, const std::string &table, const std::string &field_name,
                         const std::string &field_value) :
            operation_(operation_),
            table(table),
            field_name(field_name),
            field_value(field_value) {

    }

    binary_data operation::serialization_json() const {

    }

    void operation::deserialization_json(binary_data) {

    }
}
