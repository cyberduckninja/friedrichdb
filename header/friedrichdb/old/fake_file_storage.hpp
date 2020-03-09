#pragma once

#include <friedrichdb/abstract_database.hpp>
#include <vector>
#include <functional>

namespace friedrichdb {

    class file_storage_fake final : public abstract_database {
    public:

        file_storage_fake();

        auto apply(query&&) -> output_query override;

        ~file_storage_fake() override = default;


    };
}
