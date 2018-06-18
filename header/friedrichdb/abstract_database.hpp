#ifndef ABSTRACT_DATABASE_HPP
#define ABSTRACT_DATABASE_HPP

#include <unordered_map>
#include <cstdint>
#include <condition_variable>
#include <mutex>

#include <friedrichdb/query.hpp>

namespace friedrichdb {

    struct abstract_database {

        enum class storge_t : uint8_t {
            memory = 0x00,
            disk,
            instance
        };

        abstract_database(std::string , storge_t);

        ~abstract_database() = default;

        virtual auto apply(query&&) -> output_query = 0;

        storge_t type() const;
    protected:
        std::mutex              mutex;
        std::condition_variable condition_variable;


        const std::string& name() const;


    private:

        std::string name_;
        storge_t type_;
    };
}
#endif //ABSTRACT_DATABASE_HPP
