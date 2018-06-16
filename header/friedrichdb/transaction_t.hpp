#include <utility>

#pragma once

#include <cstddef>
#include <string>
#include <vector>
#include <cstdint>
#include <friedrichdb/serializable.hpp>
#include <friedrichdb/operation.hpp>


namespace friedrichdb {
    enum class transaction_status : uint8_t {
        read_memory,
        write_memory,
        await_memory,
        read_disk,
        write_disk,
        await_disk
    };

    enum class transaction_processing_status : uint8_t {

    };

    enum class transaction_operation_type : uint8_t {
        start_transaction,
        stop_transaction
    };

    using id_t = std::size_t ;


    struct transaction_t final : public serializable {
        using storage = std::vector<operation>;
        using iterator = storage::iterator;
        using const_iterator = storage::const_iterator;

        ~transaction_t() = default;

        auto begin() -> iterator  {
            return operations.begin();
        }

        auto end() -> iterator  {
            return operations.end();
        }

        template<typename... Args>
        void emplace_back(Args&&... args){
            operations.emplace_back(std::forward<Args>(args)...);
        }

        binary_data serialization_json() const override {

        }

        void deserialization_json(binary_data) override  {

        }
        id_t query_id;
        id_t id;
        transaction_status status_;
    private:
        storage operations;
    };

    struct query final : public serializable {
        using storage = std::vector<transaction_t>;
        using iterator = storage::iterator;
        using const_iterator = storage::const_iterator;


        query(std::string database) : database(std::move(database)) {}
        ~query() = default;


        auto begin() -> iterator  {
            return transactions.begin();
        }

        auto end() -> iterator  {
            return transactions.end();
        }

        binary_data serialization_json() const override {

        }

        void deserialization_json(binary_data) override  {

        }

        template<typename... Args>
        void emplace_back(Args&&... args){
            transactions.emplace_back(std::forward<Args>(args)...);
        }


        id_t id;
        std::string database;
        storage transactions;
    };

}
