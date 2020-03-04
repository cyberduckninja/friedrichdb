#pragma once

#include <memory>
#include <unordered_map>
#include <map>
#include <list>
#include <algorithm>

#include <friedrichdb/core/field_base.hpp>
#include <friedrichdb/core/table.hpp>
#include <friedrichdb/core/options.hpp>

namespace friedrichdb { namespace in_memory {

        using collection = core::collection<std::allocator>;

        struct view_collection final {
            view_collection(collection *ptr) : ptr_(ptr) {}

        private:
            collection *ptr_;
        };

        class database final {
        public:
            database(const core::database_constructor_options &options) {}

            auto remove(const core::collection_remove_options &options) -> void {

                auto it = name_to_idx_.find(options.name_);

                if (it == name_to_idx_.end()) {
                   std::cerr << "not collection" <<std::endl;
                } else {
                    auto result = storage_.begin();
                    std::advance(result,it->second);
                    storage_.erase(result);
                    name_to_idx_.erase(it);
                }
            }

            auto create(const core::collection_create_options &options) -> view_collection {
                storage_.emplace_back(new collection());
                auto result = name_to_idx_.emplace(options.name_, storage_.size());
                auto it = storage_.begin();
                std::advance(it,result.first->second);
                return  it->get();
            }

            auto find(const core::collection_find_options &options) -> view_collection {

                auto it = name_to_idx_.find(options.name_);

                if (it == name_to_idx_.end()) {
                    std::cerr << "not collection" <<std::endl;
                    return nullptr;
                } else {
                    auto result = storage_.begin();
                    std::advance(result,it->second);
                    return result->get();
                }

            }

        private:
            std::list<std::unique_ptr<collection>> storage_;
            std::map<std::string, std::size_t> name_to_idx_;
        };

}}

