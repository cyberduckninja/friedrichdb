cmake_minimum_required(VERSION 2.8)

set(project friedrichdb_test)

include_directories(../header)

list(APPEND ${project}_HEADERS

        ../header/friedrichdb/database.hpp
        ../header/friedrichdb/in-memory/in_memory_database.hpp
        ../header/friedrichdb/in-memory/in_memory_table.hpp
        ../header/friedrichdb/journal.hpp
)

list(APPEND ${project}_SOURCES
        ../sourcer/database.cpp
        ../sourcer/in-memory/in_memory_database.cpp
        ../sourcer/in-memory/in_memory_table.cpp

)



add_executable(document_test document_test.cpp ${${project}_HEADERS} ${${project}_SOURCES})
