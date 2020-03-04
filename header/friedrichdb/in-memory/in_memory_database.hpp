#pragma once

#include <memory>
#include <unordered_map>
#include <list>

namespace friedrichdb { namespace in_memory {

        struct collection final {

        };

        struct view_collection final {
            view_collection(collection*ptr):ptr_(ptr){}

        private:
            collection* ptr_;
        };

        struct create_options {
            std::string name_;
        };

        struct remove_options final {};

        struct  find_options final {};

        struct database_options final {};

        class database final {
        public:
            database(const database_options&o ){

            }

            auto remove(const remove_options&o) -> void {

            }

            auto create(const create_options& o) -> void {
                storage_.emplace_back();
                name_to_idx_.emplace(o.name_,storage_.size());
            }

            auto find(const find_options&o)   -> view_collection {

            }

        private:
            std::list<std::unique_ptr<collection>> storage_;
            std::unordered_map<std::string,std::size_t> name_to_idx_;
        };

}}

