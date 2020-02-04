#include <iostream>
#include "../../header/friedrichdb/core/field_base.hpp"

int main() {

    field_base boolean(true);
    field_base string_(std::string("1111"));
    field_base number(int(3));
    field_base number_(int(2));
    std::cerr << (number < number_) << std::endl;

    using d = std::string*;
    std::cerr << sizeof(d) ;
    return 0;
}