#pragma once

#include <friedrichdb/serializable.hpp>
#include <friedrichdb/transaction.hpp>
#include <iostream>


namespace friedrichdb {
    struct abstract_journal {
        virtual ~abstract_journal() = default;

        virtual void push(serializable &) = 0;
    };


    class dummy_journal final : public abstract_journal {
        ~dummy_journal()= default;
        void push(serializable &s) {
            std::cerr << s.serialization_json() << std::endl;
        }
    };


    class journal final : abstract_journal {
    public:
        journal() = delete;

        explicit journal(abstract_journal *journal) : ptr(journal) {}

        ~journal() = default;

        void push(serializable &s) override {
            ptr->push(s);
        }

    private:
        std::unique_ptr<abstract_journal> ptr;

    };
}
