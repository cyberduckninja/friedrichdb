#include <utility>

#pragma once

#include <cstddef>
#include <string>
#include <vector>
#include <friedrichdb/serializable.hpp>
#include <friedrichdb/operation.hpp>


namespace friedrichdb {

    struct transaction final : public serializable {
        using storage = std::vector<operation>;
        using iterator = storage::iterator;
        using const_iterator = storage::const_iterator;

        ~transaction() = default;

        auto begin() -> iterator;

        auto end() -> iterator;

        template<typename... Args>
        void emplace_back(Args&&... args){
            operations.emplace_back(std::forward<Args>(args)...);
        }

        binary_data serialization_json() const override;

        void deserialization_json(binary_data) override  {

        }
        id_t query_id;
        id_t id;
    private:
        storage operations;
    };


    class output_transaction final : public serializable {
    public:
        using storage = std::vector<output_operation>;
        using iterator = storage::iterator;

        output_transaction(const transaction& trx);

        ~output_transaction() override = default;

        binary_data serialization_json() const override;

        void deserialization_json(binary_data) override;

        auto begin() -> iterator;

        auto end() -> iterator;


        template<typename... Args>
        void emplace_back(Args &&... args) {
            outputs_.emplace_back(std::forward<Args>(args)...);
        }
        id_t query_id;
        id_t id;
        storage outputs_;
    };

}
