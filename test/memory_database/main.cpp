#include "friedrichdb/in-memory/database.hpp"
#include <iostream>

using namespace friedrichdb::core;
using namespace friedrichdb::in_memory;

int main() {
  database_constructor_options options;
  database db(options);
  collection_constructor_options collection_options;
  collection_options.name_ = "test";
  db.create(collection_options);
  collection_find_options find_options;
  find_options.name_ = "test";
  auto view = db.find(find_options);
  return 0;
}