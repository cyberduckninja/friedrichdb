#include <friedrichdb/controller.hpp>

namespace friedrichdb {

    abstract_controller::abstract_controller(abstract_journal* ptr):journal_(ptr) {

    }

    abstract_controller::abstract_controller(const controller_config &config,abstract_journal* ptr ): journal_(ptr)  {


    }

    auto abstract_controller::add_database(const std::string& name,abstract_database* memory, abstract_database* disk) -> void {
///        databases.emplace(name,query_status::proccess,memory,disk);
    }

    auto abstract_controller::add_query(query &&query_,apply_callback && callback) -> id_t {
        auto  id = std::chrono::duration_cast< std::chrono::milliseconds >(std::chrono::steady_clock::now().time_since_epoch()).count();
        data.emplace(id,{std::move(query_),std::move(callback)});
        queue_.emplace(id);

    }

    auto abstract_controller::status(id_t query_id) -> void {

    }

    io_query::io_query(const query &input,  apply_callback && callback)
        : status(), input(input), output(), callback(callback) {}
}
