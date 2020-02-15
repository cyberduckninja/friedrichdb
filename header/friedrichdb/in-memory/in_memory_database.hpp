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

        struct options {
            std::string name_;
        };


        class database final {
        public:
            auto remove(const std::string&){}

            auto create(const options& o) -> void{
                storage_.emplace_back();
                name_to_idx_.emplace(o.name_,storage_.size());
            }

            auto find(const std::string&name)   -> view_collection {

            }

        private:
            std::list<std::unique_ptr<collection>> storage_;
            std::unordered_map<std::string,std::size_t> name_to_idx_;
        };

    }
}

