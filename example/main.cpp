#include <friedrichdb/fake_file_storage.hpp>
#include "friedrichdb/table.hpp"
#include "friedrichdb/database.hpp"
#include "friedrichdb/view/positive_integer.hpp"

using friedrichdb::tuple_t;
using friedrichdb::run_time_type::string_t;
using friedrichdb::run_time_type::boolean_t;
using friedrichdb::schema;
using friedrichdb::run_time_type::positive_integer_t;
using friedrichdb::position_key;
using friedrichdb::in_memory_database;
using friedrichdb::row;
using friedrichdb::file_storage_fake;
using friedrichdb::database;
using friedrichdb::abstract_database;
using friedrichdb::response;

int main() {

    schema s{
            {"a", string_t},
            {"b", boolean_t},
            {"c", friedrichdb::run_time_type::double_t}
    };


    tuple_t d{{"a",positive_integer_t}};
    auto insert = friedrichdb::get<friedrichdb::view::positive_integer,0>(d);
    insert.set(568);

    schema s1{
            {"a",  positive_integer_t}
    };

    in_memory_database table(std::move(s1));
    table.insert(
            [&]() -> response {
                response tmp;
                tuple_t d{{"a",  positive_integer_t}};
                auto insert = friedrichdb::get<friedrichdb::view::positive_integer,0>(d);
                insert.set(568);
                tmp.emplace_back(std::move(d));
                return tmp;
            }
    );


    schema s2{
            {"a", positive_integer_t},
            {"b", positive_integer_t},
            {"c", positive_integer_t}
    };

    auto* memory = new in_memory_database(std::move(s2));
    auto* fake = new file_storage_fake;
    std::unique_ptr<abstract_database>db (new database(memory, fake));

    db->insert(
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