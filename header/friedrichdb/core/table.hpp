#pragma once

#include <boost/container/stable_vector.hpp>
#include <vector>
#include "field_base.hpp"

enum class table_type {
    row = 0x00,
    document,
    tensor
};


struct field final {
    std::string name_;
    field_base base_;
};

using row_t = std::vector<field>;
using storage_base_t = boost::container::stable_vector<std::vector<row_t>>;


struct schema final {
    table_type table_type_;
    std::vector<field_type> storage_;
};

/// base storage in memory / shm / gpu
class table final {
public:
    using iterator = storage_base_t::iterator ;
    table(const schema& current_schema):schema_(current_schema){}

    row_t& row(std::size_t index ){

    }

    auto begin() -> iterator {

    }

    auto end() -> iterator {

    }

private:
    schema schema_;
    storage_base_t storage_;
};