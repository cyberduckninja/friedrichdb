cmake_minimum_required(VERSION 2.8)

set(project friedrichdb)
project(${project} CXX)

set(CMAKE_CXX_STANDARD 11)

add_definitions(-DRAPIDJSON_HAS_STDSTRING)

add_definitions(-DRAPIDJSON_HAS_CXX11_RVALUE_REFS)

include_directories(thirdparty/rapidjson/include)

list(APPEND ${project}_HEADERS


        header/friedrichdb/in-memory/composite_key.h
        header/friedrichdb/in-memory/document.hpp
        header/friedrichdb/in-memory/in_memory_database.hpp
        header/friedrichdb/in-memory/in_memory_table.hpp

        header/friedrichdb/ql/parser.hpp

        header/friedrichdb/abstract_database.hpp
        header/friedrichdb/abstract_table.hpp
        header/friedrichdb/database.hpp
        header/friedrichdb/controller.hpp
        header/friedrichdb/fake_file_storage.hpp
        header/friedrichdb/journal.hpp
        header/friedrichdb/operation.hpp
        header/friedrichdb/query_scheduler.hpp
        header/friedrichdb/query.hpp
        header/friedrichdb/serializable.hpp
        header/friedrichdb/storage.hpp
        header/friedrichdb/transaction.hpp


)

list(APPEND ${project}_SOURCES
        sourcer/abstract_database.cpp
        sourcer/in-memory/in_memory_table.cpp
        sourcer/in-memory/in_memory_database.cpp
        sourcer/database.cpp
        sourcer/fake_file_storage.cpp
        sourcer/field_t.cpp
        sourcer/operation.cpp
        sourcer/schema.cpp
        sourcer/storage.cpp
        sourcer/tuple_t.cpp
        sourcer/type.cpp
        sourcer/query.cpp
        sourcer/transaction.cpp
        sourcer/controller.cpp
)

#add_subdirectory(test)

add_library(${project} ${${project}_HEADERS} ${${project}_SOURCES})
set_property(TARGET ${project} PROPERTY EXPORT_NAME ${project})
target_include_directories(${project} PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/header")

add_subdirectory(example)