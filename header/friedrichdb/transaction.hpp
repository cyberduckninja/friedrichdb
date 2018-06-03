#ifndef PROJECT_TRANSACTION_HPP
#define PROJECT_TRANSACTION_HPP

#include <cstddef>
#include <string>
#include <vector>

struct abstract_operation {
    std::size_t version;
    std::string method;
    std::string table;
    std::string data;
    virtual ~abstract_operation()= default;
};

struct operation:public abstract_operation {
    virtual ~operation()= default;
};

struct abstract_transaction {
    enum class transaction_status : uint8_t {
        read = 0x00,
        write,
        wait
    };
    std::size_t id;
    std::vector<abstract_operation*> operation;

    transaction_status status_;
    virtual ~abstract_transaction()= default;
};

struct transaction {

};



#endif //PROJECT_TRANSACTION_HPP
