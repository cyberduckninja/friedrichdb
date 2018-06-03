#include "friedrichdb/data_types/tuple_t.hpp"
#include <cassert>

namespace friedrichdb {


/*
    auto tuple_t::get(position_key key) -> field_ptr {
        assert(key.key <= t.size());
        assert(key.key >= 0);
        auto meta = meta_info[key.key];
        assert(meta.type == key.type);
        return t[key.key];
    }

    auto tuple_t::get(string_key key) -> field_ptr {
        auto position = index_of_name[key.key];
        auto meta = meta_info[position];
        assert(meta.type == key.type);
        return t[position];
    }
    */

}