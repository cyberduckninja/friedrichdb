cmake_minimum_required(VERSION 2.8)

set(project friedrichdb)
project(${project} CXX)

set(CMAKE_CXX_STANDARD 11)

list(APPEND ${project}_HEADERS
        include/friedrichdb/tuple/error.hpp
        include/friedrichdb/tuple/object_id.hpp
        include/friedrichdb/tuple/ordering.h
        include/friedrichdb/tuple/storage.hpp
        include/friedrichdb/tuple/time.hpp
        include/friedrichdb/tuple/timestamp.hpp


        include/friedrichdb/abstract_database.hpp
        include/friedrichdb/composite_key.hpp
        include/friedrichdb/database.hpp
        include/friedrichdb/fake_file_storage.hpp
        include/friedrichdb/schema.hpp
        include/friedrichdb/table.hpp
        include/friedrichdb/tuple.hpp
        include/friedrichdb/type.hpp
)

list(APPEND ${project}_SOURCES
        composite_key.cpp
        database.cpp
        object_id.cpp
        storage.cpp
        timestamp.cpp
        time.cpp
        table.cpp
)

add_library(${project} ${${project}_HEADERS} ${${project}_SOURCES} )
set_property(TARGET ${project} PROPERTY EXPORT_NAME ${project})
target_include_directories(${project} PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include")