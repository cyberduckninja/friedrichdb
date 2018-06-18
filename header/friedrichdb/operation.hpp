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

    class output_operation final : public serializable {
    public:

        explicit output_operation(const operation& operation_) {
            this->query_id = operation_.query_id;
            this->transaction_id = operation_.transaction_id;
            this->id = operation_.id;
            this->operation_ = operation_.operation_ ;
            this->table = operation_.table;
            this->document_key = operation_.document_key;
            this->field_name = operation_.field_name;
            this->field_value = operation_.field_value;

        }

        output_operation() = default;

        ~output_operation() override = default;

        void deserialization_json(std::string) {

        }

        std::string serialization_json() const {

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
