#include <friedrichdb/query.hpp>

namespace friedrichdb {


    output_query::output_query(const query &query_) {
        this->id = query_.id;
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
}