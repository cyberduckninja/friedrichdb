#include <friedrichdb/query.hpp>

namespace friedrichdb {


    output_query::output_query(const query &query_) {
        this->id = query_.id();
        this->database = query_.database;

    }

    auto output_query::end() -> output_query::iterator {
        return outputs_.end();
    }

    auto output_query::begin() -> output_query::iterator {
        return outputs_.begin();
    }

    binary_data output_query::serialization_json() const {

    }

    void output_query::deserialization_json(binary_data) {

    }

    auto output_query::begin() const -> output_query::const_iterator {
        return outputs_.begin();
    }

    auto output_query::end() const -> output_query::const_iterator {
        return outputs_.end();
    }

    binary_data query::serialization_json() const {

    }

    void query::deserialization_json(binary_data) {

    }

    auto query::begin() -> query::iterator {
        return transactions.begin();
    }

    auto query::end() -> query::iterator {
        return transactions.end();
    }

    void query::emplace_back(transaction &&trx) {
        trx.query_id(id_);
        trx.id = transactions.size() - 1;
        transactions.emplace_back(std::move(trx));
    }

    query::query(std::string database) : database(std::move(database)) {}
}