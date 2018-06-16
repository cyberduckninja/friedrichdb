#pragma once


#include <cstdint>
#include <string>
#include <friedrichdb/serializable.hpp>

namespace friedrichdb {

    enum class operation_type : uint8_t {
        create,
        find,
        modify,
        remove
    };

    struct operation final : public serializable {

        operation(
                operation_type operation_,
                const std::string &table,
                const std::string &document_key,
                const std::string &field_name,
                const std::string &field_value
        ) :
            operation_(operation_),
            table(table),
            document_key(document_key),
            field_name(field_name),
            field_value(field_value) {

        }

        operation()= default;

        ~operation()= default;

        binary_data serialization_json() const {

        }

        void deserialization_json(binary_data) {

        }
        id_t query_id;
        id_t transaction_id;
        id_t id;
        operation_type operation_;
        std::string    table;
        std::string    document_key;
        std::string    field_name;
        std::string    field_value;
    };


    std::string to_string(friedrichdb::operation_type type);

    operation_type from_string(std::string type);


}
