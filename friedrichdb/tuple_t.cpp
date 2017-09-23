#include "friedrichdb/tuple_t.hpp"
#include <cassert>

namespace friedrichdb {
    /// |name:type:id|name:type:id|name:type:id|
    tuple_t::tuple_t(std::initializer_list<meta_data_t> init_list) {
        std::string tmp;

        t.reserve(init_list.size());

        for (auto &i:init_list) {
            tmp.append("|");
            auto size = t.size();
            index_of_name.emplace(i.name, size);
            meta_info.emplace_back(meta_data_t{i.name, i.type});
            t.emplace_back(std::move(std::make_shared<field_t>()));
            tmp.append(i.name).append(":").append(std::to_string(size)).append(":").append(run_time_type::to_string(i.type));
            tmp.append("|");
        }

        hash_ = std::hash<std::string>()(tmp);
    }

    auto tuple_t::hash() const -> std::size_t {
        return hash_;
    }

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

}