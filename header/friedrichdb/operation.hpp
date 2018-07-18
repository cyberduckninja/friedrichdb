#pragma once


#include <cstdint>
#include <string>
#include <vector>
#include <friedrichdb/serializable.hpp>

namespace friedrichdb {

    enum class operation_type : uint8_t {
        insert,
        find,
        upsert,
        remove
    };

    struct field {
        std::string key;
        std::string value;
    };

    using fields_t = std::vector<field>;

    struct operation final : public serializable {

        operation(
                operation_type operation_,
                const std::string &table,
                const std::string &document_key
        );


        operation(
                operation_type operation_,
                const std::string &table
        );

        operation()= default;

        ~operation()= default;

        binary_data serialization_json() const;

        void deserialization_json(binary_data);

        template <typename Key, typename Value>
        void emplace(Key&& key, Value&& value){
            fields.emplace_back(std::forward<Key>(key),std::forward<Value>(value));
        }

        id_t           query_id;
        id_t           transaction_id;
        id_t           id;
        operation_type operation_;
        std::string    table;
        std::string    document_key;
        fields_t       fields;
    };

    class output_operation final : public serializable {
    public:

        explicit output_operation(const operation& operation_);

        output_operation() = default;

        ~output_operation() override = default;

        void deserialization_json(std::string);

        std::string serialization_json() const;

        id_t           query_id;
        id_t           transaction_id;
        id_t           id;
        operation_type operation_;
        std::string    table;
        std::string    document_key;
        fields_t       fields;
    };


    std::string to_string(friedrichdb::operation_type type);

    operation_type from_string(const std::string& type);


}
