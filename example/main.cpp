#include <friedrichdb/fake_file_storage.hpp>
#include "friedrichdb/table.hpp"
#include "friedrichdb/database.hpp"

int main() {

    friedrichdb::schema s{
            {"a", friedrichdb::string_t},
            {"b", friedrichdb::boolean_t},
            {"c", friedrichdb::double_t}
    };


    auto tmp = std::to_string(568);
    friedrichdb::tuple::tuple d{{"a",friedrichdb::positive_integer_t}};
    d[friedrichdb::position_key{0,friedrichdb::positive_integer_t}]->body->set(tmp.data(),tmp.length());

    friedrichdb::in_memory_database table;
    table.insert(
            [&]() -> std::vector<friedrichdb::row> {
                std::vector<friedrichdb::row> tmp;
                auto tmp_1 = std::to_string(568);
                friedrichdb::tuple::tuple d{{"a",  friedrichdb::positive_integer_t}};
                d[friedrichdb::position_key{0,friedrichdb::positive_integer_t}]->body->set(tmp_1.data(),tmp_1.length());
                tmp.emplace_back(d);
                return tmp;
            }
    );


    auto* memory = new friedrichdb::in_memory_database;
    auto* fake = new friedrichdb::file_storage_fake;
    std::unique_ptr<friedrichdb::abstract_database>db (new friedrichdb::database(memory, fake));

    db->insert(
            [&]() -> std::vector<friedrichdb::row> {
                std::vector<friedrichdb::row> tmp;
                auto tmp_1 = std::to_string(568);
                friedrichdb::tuple::tuple d{
                        {"a", friedrichdb::positive_integer_t},
                        {"b", friedrichdb::positive_integer_t},
                        {"c", friedrichdb::positive_integer_t}
                };
                d[friedrichdb::position_key{0,friedrichdb::positive_integer_t}]->body->set(tmp_1.data(),tmp_1.length());
                d[friedrichdb::position_key{1,friedrichdb::positive_integer_t}]->body->set(tmp_1.data(),tmp_1.length());
                d[friedrichdb::position_key{2,friedrichdb::positive_integer_t}]->body->set(tmp_1.data(),tmp_1.length());
                tmp.emplace_back(d);
                return tmp;
            }
    );

    return 0;

}