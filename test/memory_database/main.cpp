#include "friedrichdb/in-memory/database.hpp"
#include <iostream>

using namespace friedrichdb::core;
using namespace friedrichdb::in_memory;

int main() {
  database_constructor_options options;
  database db(options);

  return 0;
}