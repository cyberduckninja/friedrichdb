#pragma once

#include <friedrichdb/serializable.hpp>
#include <friedrichdb/transaction.hpp>

namespace friedrichdb {

    struct query final : public serializable {
        using storage = std::vector<transaction>;
        using iterator = storage::iterator;
        using const_iterator = storage::const_iterator;

        query(const std::string &database);

        ~query() override = default;

        auto begin() -> iterator;

        auto end() -> iterator;

        binary_data serialization_json() const override;

        void deserialization_json(binary_data) override;

        void emplace_back(transaction&& trx );

        auto id(id_t id) -> void;

        auto id() const -> id_t;

        std::string database;
    private:
        id_t id_;
        storage transactions;
    };


    class output_query final : public serializable {
    public:
        using storage = std::vector<output_transaction>;
        using iterator = storage::iterator;
        using const_iterator = storage::const_iterator;

        output_query() = default;

        output_query(const output_query &) = default;

        output_query(output_query &&) = default;

        output_query &operator=(const output_query &) = default;

        output_query &operator=(output_query &&) = default;

        output_query(const query &query_);

        ~output_query() override = default;

        binary_data serialization_json() const override;

        void deserialization_json(binary_data) override;

        auto begin() -> iterator;

        auto end() -> iterator;

        auto begin() const -> const_iterator;

        auto end() const -> const_iterator;

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