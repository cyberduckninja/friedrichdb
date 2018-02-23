#ifndef FILE_STORAGE_HPP
#define FILE_STORAGE_HPP

#include "abstract_database.hpp"
#include <vector>
#include <functional>
namespace friedrichdb {
    class file_storage_fake final : public abstract_database {
    public:

        file_storage_fake():abstract_database(storge_t::disk){}

        ~file_storage_fake(){}

        abstract_table *table(const std::string &name) {
            return nullptr;
        }
        abstract_table *table(const std::string &name) const {
            return nullptr;
        }
        bool table(const std::string &, abstract_table *) {
            return true;
        }
        bool table(schema&&){
            return true;
        }
    };
}
#endif //VERSIONS_FILE_STORAGE_HPP
