#pragma once

#include <memory>

#include <friedrichdb/abstract_database.hpp>

namespace friedrichdb {

    struct database final {

        database(const std::string &name, abstract_database*memory);
        database(const std::string &name, abstract_database*memory, abstract_database*file);

        std::string name;
        std::unique_ptr<abstract_database> memory;
        std::unique_ptr<abstract_database> file;
    };


}

