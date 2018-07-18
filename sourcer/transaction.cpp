#include <friedrichdb/transaction.hpp>



namespace friedrichdb {


    output_transaction::output_transaction(const transaction &trx) {
        this->query_id = trx.query_id();
        this->id       = trx.id;
    }

    binary_data output_transaction::serialization_json() const {

    }

    void output_transaction::deserialization_json(binary_data) {

    }

    auto output_transaction::begin() -> output_transaction::iterator {
        return outputs_.begin();
    }

    auto output_transaction::end() -> output_transaction::iterator {
        return outputs_.end();
    }

    auto output_transaction::begin() const -> output_transaction::const_iterator {
        return outputs_.begin();
    }

    auto output_transaction::end() const -> output_transaction::const_iterator {
        return outputs_.end();
    }

    auto transaction::begin() -> transaction::iterator {
        return operations.begin();
    }

    auto transaction::end() -> transaction::iterator {
        return operations.end();
    }

    binary_data transaction::serialization_json() const {

    }

    void transaction::emplace_back(operation &&op) {
        op.query_id = query_id_;
        op.transaction_id = id;
        op.id = operations.size()-1;
        operations.emplace_back(std::move(op));
    }
}