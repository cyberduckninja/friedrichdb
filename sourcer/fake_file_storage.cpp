#include <friedrichdb/fake_file_storage.hpp>

namespace friedrichdb {
    file_storage_fake::file_storage_fake() : abstract_database(storage_type ::disk) {}

    auto file_storage_fake::apply(query&&) -> output_query {}

}