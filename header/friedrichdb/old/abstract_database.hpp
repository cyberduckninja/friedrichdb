#pragma once

#include <unordered_map>
#include <cstdint>
#include <condition_variable>
#include <mutex>

#include <friedrichdb/query.hpp>

namespace friedrichdb {

    enum class storage_type : uint8_t {
        memory = 0x00,
        disk
    };

    struct abstract_database {

        abstract_database(storage_type);

        virtual ~abstract_database() = default;

        virtual auto apply(query&&) -> output_query = 0;

        storage_type type() const;
    protected:
        std::mutex              mutex;
        std::condition_variable condition_variable;

    private:
        storage_type type_;
    };
}
