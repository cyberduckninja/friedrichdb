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

        void emplace_back(operation&& op);

        binary_data serialization_json() const override;

        void deserialization_json(binary_data) override  {

        }

       auto query_id(id_t id) -> void {
            query_id_ = id ;
            for(auto&i:operations){
                i.query_id = query_id_;
            }
        }

        auto query_id() const -> id_t {
            return query_id_;
        }


            id_t id;
    private:
        id_t query_id_;
        storage operations;
    };


    class output_transaction final : public serializable {
    public:
        using storage = std::vector<output_operation>;
        using iterator = storage::iterator;
        using const_iterator = storage::const_iterator;

        output_transaction(const transaction& trx);

        ~output_transaction() override = default;

        binary_data serialization_json() const override;

        void deserialization_json(binary_data) override;

        auto begin() -> iterator;

        auto end() -> iterator;

        auto begin() const -> const_iterator ;

        auto end() const -> const_iterator;




        template<typename... Args>
        void emplace_back(Args &&... args) {
            outputs_.emplace_back(std::forward<Args>(args)...);
        }
        id_t query_id;
        id_t id;
        storage outputs_;
    };

}
