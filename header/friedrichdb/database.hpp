#pragma once

#include <memory>
#include <string>

#include <friedrichdb/abstract_database.hpp>

namespace friedrichdb {

    struct database final  {
        database()= default;
        ~database()= default;
        database(const std::string &name, abstract_database*memory);
        database(const std::string &name, abstract_database*memory, abstract_database*file);

        std::string name;
    private:
        std::mutex mtx;
        std::condition_variable cv;
        std::unique_ptr<abstract_database> memory;
        std::unique_ptr<abstract_database> file;
    };


}

