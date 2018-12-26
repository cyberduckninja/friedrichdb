#include <iostream>

#include <friedrichdb/database.hpp>
#include <friedrichdb/in-memory/in_memory_database.hpp>
#include <friedrichdb/fake_file_storage.hpp>
#include <friedrichdb/query.hpp>
#include <friedrichdb/controller.hpp>



int main() {
    friedrichdb::controller_config cc;
    friedrichdb::controller cntrllr(cc);

    cntrllr.create_database("test",new friedrichdb::in_memory::in_memory_database,new friedrichdb::file_storage_fake);

    /// create
    {
        /// start
        auto op = friedrichdb::make_operation(friedrichdb::operation_type::insert,"comment","1qaz2wsx3edc");
        op.emplace("comment_data_name","comment_data_value");
        friedrichdb::query q("test");
        friedrichdb::transaction transaction;
        transaction.emplace_back(std::move(op));
        q.emplace_back(std::move(transaction));
        cntrllr.apply(std::move(q),[](const friedrichdb::output_query&out){
            std::cerr<<"!!!!!!!!!!!!!!!!!!!!!!!"<<std::endl;
            std::cerr<<"-----------------------"<<std::endl;
            std::cerr<<out.database<<std::endl;
            std::cerr<<"-----------------------"<<std::endl;
            for(const auto&trx:out){
                std::cerr<<std::to_string(trx.query_id)<<std::endl;
                std::cerr<<std::to_string(trx.id)<<std::endl;
                for(const auto&op:trx){
                    std::cerr<<op.query_id<<std::endl;
                    std::cerr<<op.transaction_id<<std::endl;
                    std::cerr<<op.id<<std::endl;
                    //std::cerr<<op.field_value<<std::endl;
                }
            }
            /// stop

            std::cerr<<"!!!!!!!!!!!!!!!!!!!!!!!"<<std::endl;
        });
    }

    /// find
    {
        /// start
        auto op = friedrichdb::make_operation(friedrichdb::operation_type::find,"comment","1qaz2wsx3edc");
        op.emplace("comment_data_name","");
        friedrichdb::query q("test");
        friedrichdb::transaction transaction;
        transaction.emplace_back(std::move(op));
        q.emplace_back(std::move(transaction));
        cntrllr.apply(std::move(q),[](const friedrichdb::output_query&out){
            std::cerr<<"!!!!!!!!!!!!!!!!!!!!!!!"<<std::endl;
            std::cerr<<"-----------------------"<<std::endl;
            std::cerr<<out.database<<std::endl;
            std::cerr<<"-----------------------"<<std::endl;
            for(const auto&trx:out){
                std::cerr<<std::to_string(trx.query_id)<<std::endl;
                std::cerr<<std::to_string(trx.id)<<std::endl;
                for(const auto&op:trx){
                    std::cerr<<op.query_id<<std::endl;
                    std::cerr<<op.transaction_id<<std::endl;
                    std::cerr<<op.id<<std::endl;
                    //std::cerr<<op.field_value<<std::endl;
                }
            }
            /// stop

            std::cerr<<"!!!!!!!!!!!!!!!!!!!!!!!"<<std::endl;
        });

    }


    /// modify
    {
        /// start
        auto op = friedrichdb::make_operation(friedrichdb::operation_type::upsert,"comment","1qaz2wsx3edc");
        op.emplace("comment_data_name","comment_data_value_1");
        friedrichdb::query q("test");
        friedrichdb::transaction transaction;
        transaction.emplace_back(std::move(op));
        q.emplace_back(std::move(transaction));
        cntrllr.apply(std::move(q), [](const friedrichdb::output_query &out) {
            std::cerr << "!!!!!!!!!!!!!!!!!!!!!!!" << std::endl;
            std::cerr << "-----------------------" << std::endl;
            std::cerr << out.database << std::endl;
            std::cerr << "-----------------------" << std::endl;
            for ( const auto &trx:out) {
                std::cerr << std::to_string(trx.query_id) << std::endl;
                std::cerr << std::to_string(trx.id) << std::endl;
                for (const auto &op:trx) {
                    std::cerr << op.query_id << std::endl;
                    std::cerr << op.transaction_id << std::endl;
                    std::cerr << op.id << std::endl;
                    ///std::cerr << op.field_value << std::endl;
                }
            }
            /// stop

            std::cerr << "!!!!!!!!!!!!!!!!!!!!!!!" << std::endl;
        });
    }


    /// find
        {
            /// start
            auto op = friedrichdb::make_operation(friedrichdb::operation_type::find,"comment","1qaz2wsx3edc");
            op.emplace("comment_data_name","");
            friedrichdb::query q("test");
            friedrichdb::transaction transaction;
            transaction.emplace_back(std::move(op));
            q.emplace_back(std::move(transaction));
            cntrllr.apply(std::move(q), [](const friedrichdb::output_query &out) {
                std::cerr << "!!!!!!!!!!!!!!!!!!!!!!!" << std::endl;
                std::cerr << "-----------------------" << std::endl;
                std::cerr << out.database << std::endl;
                std::cerr << "-----------------------" << std::endl;
                for (const auto &trx:out) {
                    std::cerr << std::to_string(trx.query_id) << std::endl;
                    std::cerr << std::to_string(trx.id) << std::endl;
                    for (const auto &op:trx) {
                        std::cerr << op.query_id << std::endl;
                        std::cerr << op.transaction_id << std::endl;
                        std::cerr << op.id << std::endl;
                        //std::cerr << op.field_value << std::endl;
                    }
                }
                /// stop

                std::cerr << "!!!!!!!!!!!!!!!!!!!!!!!" << std::endl;
            });
        }





        ///remove
        {
            /// start
            auto op = friedrichdb::make_operation(friedrichdb::operation_type::remove,"comment","1qaz2wsx3edc");
            op.emplace("comment_data_name","");
            friedrichdb::query q("test");
            friedrichdb::transaction transaction;
            transaction.emplace_back(std::move(op));
            q.emplace_back(std::move(transaction));
            cntrllr.apply(std::move(q), [](const friedrichdb::output_query &out) {
                std::cerr << "!!!!!!!!!!!!!!!!!!!!!!!" << std::endl;
                std::cerr << "-----------------------" << std::endl;
                std::cerr << out.database << std::endl;
                std::cerr << "-----------------------" << std::endl;
                for (const auto &trx:out) {
                    std::cerr << std::to_string(trx.query_id) << std::endl;
                    std::cerr << std::to_string(trx.id) << std::endl;
                    for (const auto &op:trx) {
                        std::cerr << op.query_id << std::endl;
                        std::cerr << op.transaction_id << std::endl;
                        std::cerr << op.id << std::endl;
                        //std::cerr << op.field_value << std::endl;
                    }
                }
                /// stop

                std::cerr << "!!!!!!!!!!!!!!!!!!!!!!!" << std::endl;
            });
        }



    /// find
    {
        /// start
        auto op = friedrichdb::make_operation(friedrichdb::operation_type::find,"comment","1qaz2wsx3edc");
        op.emplace("comment_data_name","");
        friedrichdb::query q("test");
        friedrichdb::transaction transaction;
        transaction.emplace_back(std::move(op));
        q.emplace_back(std::move(transaction));
        cntrllr.apply(std::move(q), [](const friedrichdb::output_query &out) {
            std::cerr << "!!!!!!!!!!!!!!!!!!!!!!!" << std::endl;
            std::cerr << "-----------------------" << std::endl;
            std::cerr << out.database << std::endl;
            std::cerr << "-----------------------" << std::endl;
            for (const auto &trx:out) {
                std::cerr << std::to_string(trx.query_id) << std::endl;
                std::cerr << std::to_string(trx.id) << std::endl;
                for (const auto &op:trx) {
                    std::cerr << op.query_id << std::endl;
                    std::cerr << op.transaction_id << std::endl;
                    std::cerr << op.id << std::endl;
                    //std::cerr << op.field_value << std::endl;
                }
            }
            /// stop

            std::cerr << "!!!!!!!!!!!!!!!!!!!!!!!" << std::endl;
        });
    }

    return cntrllr.run();
}