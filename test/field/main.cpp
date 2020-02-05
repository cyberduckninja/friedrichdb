#include <iostream>
#include "../../header/friedrichdb/core/field_base.hpp"

int main() {

    field_base boolean(true);
    field_base string_("1111");
    field_base number(int(3));
    field_base number_(int(2));

    field_base map_ = field_base::object();
    map_.emplace("qq",1);
    auto&d = map_.at("qq");

    field_base array_ = field_base::array();
    array_.emplace_back(1);
    array_.emplace_back(2);
    auto&d1 = array_.at(0);

    std::cerr << (number < number_) << std::endl;
    return 0;
}