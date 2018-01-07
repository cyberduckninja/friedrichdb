#include <friedrichdb/fake_file_storage.hpp>
#include "friedrichdb/in-memory/in_memory_database.hpp"
#include "friedrichdb/database.hpp"
#include "friedrichdb/objects/positive_integer.hpp"

using friedrichdb::tuple_t;
using friedrichdb::run_time_type::string_t;
using friedrichdb::run_time_type::boolean_t;
using friedrichdb::schema;
using friedrichdb::run_time_type::positive_integer_t;
using friedrichdb::position_key;
using friedrichdb::row;
using friedrichdb::file_storage_fake;
using friedrichdb::database;
using friedrichdb::abstract_table;
using friedrichdb::response;

int main() {

    schema s{
            "MultiVersionConcurrencyControl",
            {
                    {"a", string_t},
                    {"b", boolean_t},
                    {"c", friedrichdb::run_time_type::double_t}
            },
            {"a"}
    };


    tuple_t d{{"a",positive_integer_t}};
    auto insert = friedrichdb::get<friedrichdb::view::positive_integer,0>(d);
    insert.set(568);

    schema s0{
            "MultiVersionConcurrencyControl",
            {
                    {"a", positive_integer_t},
            },
            {}
    };

    friedrichdb::in_memory::in_memory_database t;
    t.table(std::move(s0));
    t.table("MultiVersionConcurrencyControl")->insert(
            [&]() -> response {
                response tmp;
                tuple_t d{{"a",  positive_integer_t}};
                auto insert = friedrichdb::get<friedrichdb::view::positive_integer,0>(d);
                insert.set(568);
                tmp.emplace_back(std::move(d));
                return tmp;
            }
    );


    schema s1{
            "MultiVersionConcurrencyControl",
            {
                    {"a", string_t},
                    {"b", boolean_t},
                    {"c", friedrichdb::run_time_type::double_t}
            },
            {"a"}
    };

    auto* memory = new friedrichdb::in_memory::in_memory_database;
    memory->table(std::move(s1));

    auto* fake = new file_storage_fake;
    auto* db_=new database(memory, fake);
    std::unique_ptr<friedrichdb::abstract_database>db (db_);

    db->table("MultiVersionConcurrencyControl")->insert(
            [&]() -> response {
                response tmp;
                tuple_t d{
                        {"a", positive_integer_t},
                        {"b", positive_integer_t},
                        {"c", positive_integer_t}
                };
                auto insert = friedrichdb::get<friedrichdb::view::positive_integer,0>(d);
                insert.set(568);
                insert = friedrichdb::get<friedrichdb::view::positive_integer,1>(d);
                insert.set(568);
                insert = friedrichdb::get<friedrichdb::view::positive_integer,2>(d);
                insert.set(568);
                tmp.emplace_back(std::move(d));
                return tmp;
            }
    );

    return 0;

}