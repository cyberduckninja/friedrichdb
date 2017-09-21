cmake_minimum_required(VERSION 2.8)

set(project friedrichdb)
project(${project} CXX)

set(CMAKE_CXX_STANDARD 11)

list(APPEND ${project}_HEADERS
        include/friedrichdb/error.hpp
        include/friedrichdb/meta_data_t.hpp
        include/friedrichdb/object_id.hpp
        include/friedrichdb/ordering.h
        include/friedrichdb/storage.hpp
        include/friedrichdb/time.hpp
        include/friedrichdb/timestamp.hpp


        include/friedrichdb/abstract_database.hpp
        include/friedrichdb/composite_key.hpp
        include/friedrichdb/database.hpp
        include/friedrichdb/fake_file_storage.hpp
        include/friedrichdb/schema.hpp
        include/friedrichdb/table.hpp
        include/friedrichdb/tuple_t.hpp
        include/friedrichdb/type.hpp
)

list(APPEND ${project}_SOURCES
        composite_key.cpp
        database.cpp
        object_id.cpp
        storage.cpp
        table.cpp
        time.cpp
        timestamp.cpp
        tuple_t.cpp
)

add_library(${project} ${${project}_HEADERS} ${${project}_SOURCES} include/friedrichdb/view.hpp include/friedrichdb/field_t.hpp field_t.cpp)
set_property(TARGET ${project} PROPERTY EXPORT_NAME ${project})
target_include_directories(${project} PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include")