#include "include/friedrichdb/table.hpp"
#include "friedrichdb/data_types/object_id.hpp"
namespace friedrichdb {
    response in_memory_database::find(where f) const {
        response tmp;
/*
        for (const auto &i:t_) {
            if (f(i.second)) {
                tmp.insert(i.second);
            }
        };
*/
        return tmp;
    }

    bool in_memory_database::update(where_generator f) {
        /*
        for(auto it = t_.begin(); it!=t_.end(); ) {
            if(f(it->second)){
                it = t_.erase(it);
            } else {
                ++it;
            }
        }
         */
        return true;
    }

    bool in_memory_database::erase(where f) {
        /*
        for(auto it = t_.begin(); it!=t_.end(); ) {

            if(f(it->second)){
                it = t_.erase(it);
            } else {
                ++it;
            }
        }
         */
        return true;
    }

    bool in_memory_database::insert(generator f) {

        for(auto &&i:f()){
            auto tmp = data_types::object_id().generate();
            auto size = t_.size();
            current_schema.check(i);
            t_.emplace(composite_key{tmp,size},std::move(i));
        }

        return true;
    }

    in_memory_database::in_memory_database(schema &&current_schema) : current_schema(std::move(current_schema)),abstract_database(storge_t::memory){}


}
