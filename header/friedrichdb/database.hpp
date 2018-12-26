#pragma once

#include <memory>
#include <string>

#include <friedrichdb/abstract_database.hpp>

namespace friedrichdb {

    class database final  {
    public:
        database() = default;
        database(database&&) = default;
        database&operator=(database&&) = default;
        database(const database&) = delete;
        database&operator=(const database&) = delete;
        ~database() = default;
        database(const std::string &name, abstract_database*memory);
        database(const std::string &name, abstract_database*memory, abstract_database*file);

        auto name() -> const std::string&;

    private:
        std::string name_;
        std::mutex mtx;
        std::condition_variable cv;
        std::unique_ptr<abstract_database> memory;
        std::unique_ptr<abstract_database> file;
    };


}

