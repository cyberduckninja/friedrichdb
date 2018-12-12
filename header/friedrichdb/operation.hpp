#pragma once


#include <cstdint>
#include <string>
#include <vector>
#include <friedrichdb/serializable.hpp>
#include <friedrichdb/document.hpp>

namespace friedrichdb {

    enum class operation_type : unsigned char {
        insert,
        find,
        update,
        upsert,
        replace,
        remove
    };


    struct operation final : public serializable {

        operation()= default;

        ~operation()= default;

        binary_data serialization_json() const;

        void deserialization_json(binary_data);

        template <typename Key, typename Value>
        void emplace(Key&& key, Value&& value){
            embedded_document_.fields.emplace_back(std::forward<Key>(key),std::forward<Value>(value));
        }

        id_t                         query_id;
        id_t                         transaction_id;
        id_t                         id;
        operation_type               operation_;
        std::string                  collection;
        embedded_document embedded_document_;
    };

    class output_operation final : public serializable {
    public:

        explicit output_operation(const operation& operation_);

        output_operation() = default;

        ~output_operation() override = default;

        void deserialization_json(binary_data);

        binary_data serialization_json() const;

        id_t                         query_id;
        id_t                         transaction_id;
        id_t                         id;
        operation_type               operation_;
        std::string                  collection;
        embedded_document embedded_document_;
    };


    std::string to_string(friedrichdb::operation_type type);

    operation_type from_string(const std::string& type);


}
