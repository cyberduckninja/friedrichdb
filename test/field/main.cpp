#include <iostream>
#include "../../header/friedrichdb/base/flat_field.hpp"

int main() {

    flat_field boolean(true);
    flat_field string_(std::string("1111"));
    flat_field number(int(3));
    flat_field number_(int(2));
    std::cerr << (number < number_) << std::endl;

    using d = std::string*;
    std::cerr << sizeof(d) ;
    return 0;
}