#ifndef FILE_STORAGE_HPP
#define FILE_STORAGE_HPP

#include "abstract_database.hpp"
#include <vector>
#include <functional>

namespace friedrichdb {
    class file_storage_fake final : public abstract_database {
    public:

        file_storage_fake();

        auto apply(query&&) -> output_query override;

        ~file_storage_fake();


    };
}
#endif //VERSIONS_FILE_STORAGE_HPP
