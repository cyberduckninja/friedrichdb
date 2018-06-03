#ifndef PROJECT_JOURNAL_HPP
#define PROJECT_JOURNAL_HPP

#include <friedrichdb/transaction.hpp>

//0,1,2,3 -> ...

class abstract_journal {
    virtual bool write_transaction(transaction& t )=0;
    virtual bool update_status_transaction(transaction& t )=0;
    virtual void read_transaction() = 0;
};



class journal final {

private:
    std::unique_ptr<abstract_journal> ptr;
};
#endif //PROJECT_JOURNAL_HPP
