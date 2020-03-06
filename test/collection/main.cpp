#include "friedrichdb/core/basic_field.hpp"
#include "friedrichdb/core/collection.hpp"
#include <iostream>

using namespace friedrichdb::core;

int main() {
    basic_schema_t<std::allocator> schema;
    schema.push("hahahahaha",field_type::boolean);
    assert(schema.begin()->type_ == field_type::boolean);
    collection<std::allocator> c(schema);

    collection<std::allocator> c1(schema);

    c1.update(c);
    
    return 0;
}