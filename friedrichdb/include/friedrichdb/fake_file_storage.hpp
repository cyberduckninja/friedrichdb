#ifndef FILE_STORAGE_HPP
#define FILE_STORAGE_HPP

#include "abstract_database.hpp"
#include <vector>
#include <functional>
namespace friedrichdb {
    class file_storage_fake : public abstract_database {
    public:

        file_storage_fake():abstract_database(storge_t::disk){}

        ~file_storage_fake() = default;

        response find(where) const override {
            response tmp;
            return tmp;
        }

        bool update(where_generator) override {
            return true;
        }


        bool erase(where) override {
            return true;
        }


        bool insert(generator) override {
            return true;
        }
    };
}
#endif //VERSIONS_FILE_STORAGE_HPP
