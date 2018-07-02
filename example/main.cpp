#include <iostream>

#include <friedrichdb/database.hpp>
#include <friedrichdb/in-memory/in_memory_database.hpp>
#include <friedrichdb/fake_file_storage.hpp>
#include <friedrichdb/query.hpp>
#include <friedrichdb/controller.hpp>

struct dummu_excutor{

};

int main() {

    friedrichdb::controller<dummu_excutor> cntrllr;


    cntrllr.add_database("test",new friedrichdb::in_memory::in_memory_database,new friedrichdb::file_storage_fake);

    /// create
    {
        /// start
        friedrichdb::operation op;
        op.operation_ = friedrichdb::operation_type::insert;
        op.table = "comment";
        op.document_key = "1qaz2wsx3edc";
        op.field_name = "comment_data_name";
        op.field_value = "comment_data_value";
        friedrichdb::query q(std::string("test"));
        friedrichdb::transaction transaction;
        transaction.emplace_back(op);
        q.emplace_back(transaction);
        cntrllr.apply(std::move(q));
        /// stop
    }

    /// find
    {
        /// start
        friedrichdb::operation op;
        op.operation_ = friedrichdb::operation_type::find;
        op.table = "comment";
        op.document_key = "1qaz2wsx3edc";
        op.field_name = "comment_data_name";
        friedrichdb::query q(std::string("test"));
        friedrichdb::transaction transaction;
        transaction.emplace_back(op);
        q.emplace_back(transaction);
        auto out = db.apply(std::move(q));
        std::cerr<<"!!!!!!!!!!!!!!!!!!!!!!!"<<std::endl;
        std::cerr<<"-----------------------"<<std::endl;
        std::cerr<<out.database<<std::endl;
        std::cerr<<"-----------------------"<<std::endl;
        for(auto&trx:out){
            std::cerr<<std::to_string(trx.query_id)<<std::endl;
            std::cerr<<std::to_string(trx.id)<<std::endl;
            for(auto&op:trx){
                std::cerr<<op.query_id<<std::endl;
                std::cerr<<op.transaction_id<<std::endl;
                std::cerr<<op.id<<std::endl;
                std::cerr<<op.field_value<<std::endl;
            }
        }
        /// stop

        std::cerr<<"!!!!!!!!!!!!!!!!!!!!!!!"<<std::endl;
    }


    /// modify
    {
        /// start
        friedrichdb::operation op;
        op.operation_ = friedrichdb::operation_type::upsert;
        op.table = "comment";
        op.document_key = "1qaz2wsx3edc";
        op.field_name = "comment_data_name";
        op.field_value = "comment_data_value_1";
        friedrichdb::query q(std::string("test"));
        friedrichdb::transaction transaction;
        transaction.emplace_back(op);
        q.emplace_back(transaction);
        auto out = db.apply(std::move(q));
        std::cerr<<"!!!!!!!!!!!!!!!!!!!!!!!"<<std::endl;
        std::cerr<<"-----------------------"<<std::endl;
        std::cerr<<out.database<<std::endl;
        std::cerr<<"-----------------------"<<std::endl;
        for(auto&trx:out){
            std::cerr<<std::to_string(trx.query_id)<<std::endl;
            std::cerr<<std::to_string(trx.id)<<std::endl;
            for(auto&op:trx){
                std::cerr<<op.query_id<<std::endl;
                std::cerr<<op.transaction_id<<std::endl;
                std::cerr<<op.id<<std::endl;
                std::cerr<<op.field_value<<std::endl;
            }
        }
        /// stop

        std::cerr<<"!!!!!!!!!!!!!!!!!!!!!!!"<<std::endl;
    }


    /// find
    {
        /// start
        friedrichdb::operation op;
        op.operation_ = friedrichdb::operation_type::find;
        op.table = "comment";
        op.document_key = "1qaz2wsx3edc";
        op.field_name = "comment_data_name";
        friedrichdb::query q(std::string("test"));
        friedrichdb::transaction transaction;
        transaction.emplace_back(op);
        q.emplace_back(transaction);
        auto out = db.apply(std::move(q));
        std::cerr<<"!!!!!!!!!!!!!!!!!!!!!!!"<<std::endl;
        std::cerr<<"-----------------------"<<std::endl;
        std::cerr<<out.database<<std::endl;
        std::cerr<<"-----------------------"<<std::endl;
        for(auto&trx:out){
            std::cerr<<std::to_string(trx.query_id)<<std::endl;
            std::cerr<<std::to_string(trx.id)<<std::endl;
            for(auto&op:trx){
                std::cerr<<op.query_id<<std::endl;
                std::cerr<<op.transaction_id<<std::endl;
                std::cerr<<op.id<<std::endl;
                std::cerr<<op.field_value<<std::endl;
            }
        }
        /// stop

        std::cerr<<"!!!!!!!!!!!!!!!!!!!!!!!"<<std::endl;
    }

    return 0;
}