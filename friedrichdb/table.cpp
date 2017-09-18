#include "include/friedrichdb/table.hpp"
#include "friedrichdb/tuple/object_id.hpp"
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
        for(auto it = t_.begin(); it!=t_.end(); ) {
            if(f(it->second)){
                it = t_.erase(it);
            } else {
                ++it;
            }
        }
        return true;
    }

    bool in_memory_database::insert(generator f) {
        for(const auto &i:f()){
            auto tmp = tuple::object_id().generate();
            auto size = t_.size();
            t_.emplace(composite_key{tmp,size},i);
        }
        return true;
    }


}
