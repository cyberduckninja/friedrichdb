#pragma once

#include <utility>
#include <mutex>
#include <condition_variable>
#include <functional>
#include <string>

#include <friedrichdb/operation.hpp>
#include <friedrichdb/output.hpp>
#include <friedrichdb/transaction_t.hpp>


namespace friedrichdb {

    enum class table_storage_type {
        memory = 0x00,
        persistent
    };

    class abstract_table {
    public:
        abstract_table(std::string name):name_(std::move(name)){}

        virtual ~abstract_table() = default;

        virtual auto apply(transaction_t) -> output_transaction = 0;

    protected:
        const std::string& name() const {
            return name_;
        }

        std::mutex  mutext;
        std::condition_variable condition_variable;

    private:
        std::string name_;
    };
}

