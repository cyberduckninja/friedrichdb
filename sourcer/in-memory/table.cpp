#include "friedrichdb/in-memory/table.hpp"
#include "friedrichdb/data_types/object_id.hpp"

namespace friedrichdb {
    namespace in_memory {
        response table::find(std::initializer_list<std::string> index_id, where f) const {
            response tmp;
            auto hash = std::size_t(1);//TODO BigProblem
            /*if (hash_index(hash)) {
                auto index = index_manager.at(hash);
                auto addres = index->find(f);
                for (const auto &i:addres) {
                    tmp.emplace_back(pm.current_row(i));
                }
            } else {
                return tmp;
            }*/

            return tmp;
        }

        bool table::update(where_generator f) {
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

        bool table::erase(where f) {
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

        bool table::insert(generator f) {
            bool status = false;
            for (auto &&i:f()) {
                pm.push_back(std::move(i));
            }

            return true;
        }

        table::table(schema &&current_schema) : current_schema(std::move(current_schema)){}

        auto table::index(const std::string &name) -> abstract_index * {
            /*
            auto it = index_manager.find(name);
            abstract_index *index;
            if (it == index_manager.end()) {
                index = nullptr;
            } else {
                index = it->second.get();
            }
            return index;
             */
        }


        auto table::index(const std::string &name) const -> abstract_index * {
            /*
            auto it = index_manager.find(name);
            abstract_index *index;
            if (it == index_manager.end()) {
                index = nullptr;
            } else {
                index = it->second.get();
            }
            return index;
             */
        }

        auto table::index(const std::string &name, abstract_index *index) -> bool {
            /*
            auto it = index_manager.emplace(name, index);
            return it.second;
             */
        }

    }
}
