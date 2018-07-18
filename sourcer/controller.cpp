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

        auto it = databases.find(query_.database);
        if (it == databases.end()) {
            add_database(query_.database, new in_memory::in_memory_database, nullptr);
        }

        auto  id = std::chrono::duration_cast< std::chrono::milliseconds >(std::chrono::steady_clock::now().time_since_epoch()).count();
        data.emplace(id,io_query(std::move(query_),std::move(callback)));
        queue_.emplace(id);
        return id;
    }

    auto abstract_controller::status(id_t query_id,status_callback&& callback) -> void {
        callback(data.at(query_id).status,data.at(query_id).output);
    }

    io_query::io_query(const query &input,  apply_callback && callback)
        : status(), input(input), output(), callback(std::move(callback)) {}
}
