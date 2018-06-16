#include <friedrichdb/database.hpp>
#include <friedrichdb/in-memory/in_memory_database.hpp>
#include <friedrichdb/fake_file_storage.hpp>
int main () {
    auto* memory = new friedrichdb::in_memory::in_memory_database;
    auto* disk = new friedrichdb::file_storage_fake;
    friedrichdb::database db(std::string("test"),memory,disk);
    friedrichdb::operation op;
    op.operation_= friedrichdb::operation_type::create;
    op.table = "comment";
    op.field_name = "comment_data_name";
    op.field_value = "comment_data_value";
    friedrichdb::query q(std::string("test"));
    friedrichdb::transaction_t transaction;
    transaction.emplace_back(op);
    q.emplace_back(transaction);
    db.apply(std::move(q));


    return 0;
}