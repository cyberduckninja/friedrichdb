#include <friedrichdb/fake_file_storage.hpp>
namespace friedrichdb {
    file_storage_fake::file_storage_fake() : abstract_database("disk", storge_t::disk) {}

    auto file_storage_fake::apply(query&&) -> output_query {}

    file_storage_fake::~file_storage_fake() {}

}