#pragma once

#include <vector>
#include <string>

#include <friedrichdb/abstract_database.hpp>
#include <friedrichdb/database.hpp>
#include <friedrichdb/journal.hpp>
#include <friedrichdb/query_scheduler.hpp>
#include <friedrichdb/in-memory/in_memory_database.hpp>
#include <chrono>
#include <thread>

/// run - time
namespace friedrichdb {

    enum class query_status {
        wait = 0x00,
        good,
        bad,
        proccess
    };

    using apply_callback = std::function<void(const output_query &)>;
    using status_callback = std::function<void(query_status, const output_query &)>;

    struct engine final {
        storge_t type;
    };

    struct database_config {
        std::string name;
        engine engine_;
    };

    struct io_query final {
        io_query(const query &input, apply_callback &&callback);

        query_status status;
        query input;
        output_query output;
        apply_callback callback;

    };

    using controller_config = std::initializer_list<database_config>;

    struct abstract_controller {
        abstract_controller(std::size_t worker_count, abstract_journal *);

        abstract_controller(abstract_journal *);

        virtual ~abstract_controller() = default;

        auto add_query(query &&, apply_callback &&callback) -> id_t;

        auto create_database(const std::string &, abstract_database *, abstract_database *) -> void;

        auto status(id_t, status_callback &&) -> void;


    protected:
        std::size_t worker_count;
        std::mutex mtx;
        std::condition_variable cv;
        journal journal_;
        std::unordered_map<std::string, database> databases;
        std::queue<id_t> queue_;
        std::unordered_map<id_t, io_query> data;
    };


    /// standalone

    class controller final : public abstract_controller {
    public:
        using unique_lock =  std::unique_lock<std::mutex>;

        controller() : abstract_controller(new dummy_journal) {

        }

        controller(const controller_config &config,std::size_t worker_counter) : abstract_controller(worker_counter, new dummy_journal) {

        }

        controller(std::size_t worker_counter) : abstract_controller(worker_counter, new dummy_journal) {

        }

        ~controller() = default;

        auto apply(query &&query_, apply_callback &&callback) -> id_t {
            id_t id;


            {
                unique_lock lock(mtx);
                id = add_query(std::move(query_), std::move(callback));
            }

            return id;
        }

        auto run() -> std::size_t {
            {
                unique_lock lock(mtx);
                cv.wait(lock,[&](){ return !queue_.empty(); });
                while(!queue_.empty()){
                    /*
                    auto id = queue_.front();
                    queue_.pop();
                    auto&d = data.at(id);
                    auto&db = databases.at(d.input.database);
                   db
                     */

                }
            }
        }

    private:

    };


}