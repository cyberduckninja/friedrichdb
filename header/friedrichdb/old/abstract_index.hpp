#pragma once

#include <utility>
#include <mutex>
#include <condition_variable>
#include <functional>
#include <string>

#include <friedrichdb/operation.hpp>
#include <friedrichdb/transaction.hpp>


namespace friedrichdb {

    enum class index_storage_type : char {
        memory = 0x00,
        persistent
    };

    enum class index_type : char {
       hash_index = 0x00,
       bin_index
    };

    class abstract_index {
    public:
        abstract_index(std::string name):name_(std::move(name)){

        }
        virtual ~abstract_index() = default;

    protected:
        auto name() const -> const std::string& {
            return name_;
        }

        std::mutex              mtx;
        std::condition_variable condition_variable;

    private:
        const index_storage_type index_storage_type_;
        const index_type index_type_;
        std::string name_;
    };
}
