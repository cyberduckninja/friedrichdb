#include <iostream>
#include "friedrichdb/core/table.hpp"
#include <nlohmann/json.hpp>
int main() {
    basic_schema_t<std::allocator> schema;
    collection<std::allocator> c(schema);


    return 0;
}