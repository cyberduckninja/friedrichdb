#include <friedrichdb/controller.hpp>
namespace friedrichdb {

    abstract_controller::abstract_controller(abstract_journal* ptr):journal_(ptr) {

    }

    abstract_controller::abstract_controller(const controller_config &config,abstract_journal* ptr ): journal_(ptr)  {


    }

    auto abstract_controller::add_database(const std::string& name,abstract_database* memory, abstract_database* disk) -> void {
        databases.emplace(name,memory,disk);
    }

    auto abstract_controller::add_query(query &&query_) -> id_t {

        queue_.emplace();

    }

    auto abstract_controller::status(id_t query_id) -> void {

    }
}
