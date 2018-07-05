#pragma once

#include <vector>
#include <string>

#include <friedrichdb/abstract_database.hpp>
#include <friedrichdb/database.hpp>
#include <friedrichdb/journal.hpp>
#include <friedrichdb/query_scheduler.hpp>
#include <chrono>

/// run - time
namespace friedrichdb {

    using apply_callback = std::function<void(const output_query&)>;

    struct engine final  {
        storge_t type;
    };

    struct database_config {
        std::string name;
        engine engine_;
    };

    enum class query_status {
        wait = 0x00,
        good,
        bad,
        proccess
    };


    struct io_query final {

        io_query( const query &input, apply_callback && callback);

        query_status status;
        query input;
        output_query output;
        apply_callback callback;

    };

    using controller_config = std::initializer_list<database_config>;

    struct abstract_controller  {
        abstract_controller(const controller_config &config,abstract_journal* );

        abstract_controller(abstract_journal*);

        virtual ~abstract_controller() = default;

        auto add_query(query&&,apply_callback && callback) -> id_t ;

        auto add_database(const std::string& name,abstract_database* , abstract_database* ) -> void;

        auto status(id_t) -> void;


    protected:
        std::mutex mtx;
        std::condition_variable cv;
        journal                                  journal_;
        std::unordered_map<std::string,database> databases;
        std::queue<id_t>                         queue_;
        std::unordered_map<id_t, io_query>       data;
    };



    /// standalone

    template <typename Executor>
    class controller final : public abstract_controller {
    public:
        controller():abstract_controller(new dummy_journal){}
        controller(const controller_config &config):abstract_controller(config,new dummy_journal){}
        ~controller() = default;

        auto apply(query && query_,std::function<void(const output_query&)>callback) -> id_t {

        }

        void run(){

        }

    private:

        Executor executor;
    };



}