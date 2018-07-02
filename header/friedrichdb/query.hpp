#pragma once

#include <friedrichdb/serializable.hpp>
#include <friedrichdb/transaction.hpp>

namespace friedrichdb {

    struct query final : public serializable {
        using storage = std::vector<transaction>;
        using iterator = storage::iterator;
        using const_iterator = storage::const_iterator;


        query(std::string database) : database(std::move(database)) {}

        ~query() override = default;

        auto begin() -> iterator;

        auto end() -> iterator;

        binary_data serialization_json() const override;

        void deserialization_json(binary_data) override;

        template<typename... Args>
        void emplace_back(Args &&... args) {
            transactions.emplace_back(std::forward<Args>(args)...);
        }


        id_t id;
        std::string database;
    private:
        storage transactions;
    };


    class output_query final : public serializable {
    public:
        using storage = std::vector<output_transaction>;
        using iterator = storage::iterator;

        output_query() = default;

        output_query(const output_query &) = default;

        output_query(output_query &&) = default;

        output_query &operator=(const output_query &) = default;

        output_query &operator=(output_query &&) = default;

        output_query(const query &query_);

        ~output_query() override = default;

        binary_data serialization_json() const;

        void deserialization_json(binary_data);

        auto begin() -> iterator;

        auto end() -> iterator;

        template<typename... Args>
        void emplace_back(Args &&... args) {
            outputs_.emplace_back(std::forward<Args>(args)...);
        }


        id_t id;
        std::string database;
    private:
        storage outputs_;
    };

}