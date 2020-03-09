#pragma once

#include <cstdint>
#include <string>
#include <vector>

#include <friedrichdb/serializable.hpp>
#include <friedrichdb/base/document.hpp>

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

        binary_data serialization_json() const override;

        void deserialization_json(binary_data) override;

        template <typename Key, typename Value>
        void emplace(Key&& key, Value&& value){
            flat_document_.emplace(std::forward<Key>(key),std::forward<Value>(value));
        }

        auto document_id() -> const std::string& {
            return flat_document_.document_id;
        }

        id_t           query_id;
        id_t           transaction_id;
        id_t           id;
        operation_type operation_;
        std::string    collection;
        flat_document  flat_document_;
    };

    inline auto  make_operation(friedrichdb::operation_type type,const std::string&collection,const std::string& document_id = "") -> operation {
        operation tmp ;
        tmp.operation_ = type;
        tmp.collection = collection;
        tmp.flat_document_.document_id = document_id;
        return tmp;
    }

    class output_operation final : public serializable {
    public:

        explicit output_operation(const operation& operation_);

        output_operation() = default;

        ~output_operation() override = default;

        void deserialization_json(binary_data) override;

        binary_data serialization_json() const override;

        id_t              query_id;
        id_t              transaction_id;
        id_t              id;
        operation_type    operation_;
        std::string       collection;
        flat_document embedded_document_;
    };


    std::string to_string(friedrichdb::operation_type type);

    operation_type from_string(const std::string& type);


}
