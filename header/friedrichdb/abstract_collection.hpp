#pragma once

#include <utility>
#include <mutex>
#include <condition_variable>
#include <functional>
#include <string>

#include <friedrichdb/operation.hpp>
#include <friedrichdb/transaction.hpp>


namespace friedrichdb {

    enum class table_storage_type {
        memory = 0x00,
        persistent
    };

    class abstract_collection {
    public:
        abstract_collection(std::string name);

        virtual ~abstract_collection() = default;

        virtual auto apply(transaction) -> output_transaction = 0;

    protected:
        const std::string& name() const;

        std::mutex  mutext;
        std::condition_variable condition_variable;

    private:
        std::string name_;
    };
}

