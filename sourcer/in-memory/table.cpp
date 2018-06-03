#include "friedrichdb/in-memory/table.hpp"
#include "friedrichdb/data_types/object_id.hpp"

namespace friedrichdb {
    namespace in_memory {

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
