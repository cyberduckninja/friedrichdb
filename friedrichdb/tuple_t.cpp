#include "friedrichdb/tuple_t.hpp"
#include <cassert>
namespace friedrichdb {



        tuple_t::tuple_t(std::initializer_list<meta_data_t> init_list) {
            t.reserve(init_list.size());
            for (auto &i:init_list) {
                auto size = t.size();
                index_of_name.emplace(i.name, size);
                meta_info.emplace_back(meta_data_t{i.name, i.type});
                t.emplace_back(std::move(std::make_shared<field_t>()));
            }
        }

}