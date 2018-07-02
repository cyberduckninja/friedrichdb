#pragma once

#include <vector>
#include <string>
#include <friedrichdb/abstract_database.hpp>
#include <friedrichdb/database.hpp>
#include <friedrichdb/journal.hpp>
#include <friedrichdb/query_scheduler.hpp>

/// run - time
namespace friedrichdb {


    struct engine final  {
        storge_t type;
    };

    struct database_config {
        std::string name;
        engine engine_;
    };


    struct io_query {
        query input;
        output_query output;

    };

    using controller_config = std::initializer_list<database_config>;



    struct abstract_controller  {
        abstract_controller(const controller_config &config,abstract_journal* ptr);

        abstract_controller(abstract_journal* ptr);

        virtual ~abstract_controller() = default;

        auto add_query(query&&) -> id_t ;

        auto add_database(const std::string& name,abstract_database* , abstract_database* ) -> void;

        auto status(id_t) -> void;


    protected:
        std::mutex mtx;
        std::condition_variable cv;
        journal                                  journal_;
        std::unordered_map<std::string,database> databases;
        std::queue<id_t> queue_;
        std::unordered_map<id_t, io_query> data;


    };



    /// standalone

    template <typename Executor>
    class controller final : public abstract_controller {
    public:
        controller():abstract_controller(new dummy_journal){}
        controller(const controller_config &config):abstract_controller(config,new dummy_journal){}
        ~controller() = default;

        auto apply(query && query_) -> void {
/*
            output_query output;

            auto it = databases.find(query_.database);
            if ( it != databases.end() ) {
                output = it->second.memory->apply(std::move(query_));
            } else {
                /// else
            }

            return output;


*/
        }

    private:
        Executor executor;
    };



}