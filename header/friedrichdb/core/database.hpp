#pragma once

#include <unordered_map>
#include "collection.hpp"

namespace friedrichdb ::core {

    class database_t final {
    public:
        using storage_t = std::unordered_map<std::string, std::unique_ptr<collection_t>>;
        using iterator = typename storage_t::iterator;

        auto get(const std::string &name) -> collection_t * {
            return storage_.at(name).get();
        }

        auto create(const std::string &name) -> collection_t * {
            auto result = storage_.emplace(name, std::make_unique<collection_t>());
            return result.first->second.get();
        }

        auto begin() -> iterator {
            return storage_.begin();
        }

        auto end() -> iterator {
            return storage_.end();
        }

        auto drop(const std::string& name) -> void {
            storage_.erase(name);
        }

    private:
        storage_t storage_;
    };

}