#include <iostream>
#include "friedrichdb/core/table.hpp"
#include "friedrichdb/core/field_base.hpp"
#include <nlohmann/json.hpp>
int main() {
    basic_schema_t<std::allocator> schema;
    schema.push("1",field_type::boolean);
    collection<std::allocator> c(schema);


    return 0;
}