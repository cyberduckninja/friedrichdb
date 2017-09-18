#include "friedrichdb/tuple.hpp"
namespace friedrichdb {

    namespace tuple {

        std::shared_ptr<tuple::field_t> tuple::operator[](string_key key) {
            auto position = index_of_name[key.key];
            auto meta = meta_info[position];
            assert(meta.type == key.type);
            auto tmp = t[position];
            return tmp;
        }

        std::shared_ptr<tuple::field_t> tuple::operator[](position_key key) {
            assert(key.key <= t.size());
            assert(key.key >= 0);
            auto meta = meta_info[key.key];
            assert(meta.type == key.type);
            auto tmp = t[key.key];
            return tmp;
        }

        tuple::tuple(std::initializer_list<meta_data_t> init_list) {
            t.reserve(init_list.size());
            for (auto &i:init_list) {
                auto size = t.size();
                index_of_name.emplace(i.name, size);
                meta_info.emplace_back(meta_data_t{i.name, i.type});
                t.emplace_back(std::move(std::make_shared<field_t>()));
            }
        }

        void tuple::field_t::set(const char *data, std::size_t size) {
            data_.resize(size);
            for (std::size_t i = 0; i < size; ++i) {
                data_[i] = data[i];
            }
        }



    }
}