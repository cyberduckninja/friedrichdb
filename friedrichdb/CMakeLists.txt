cmake_minimum_required(VERSION 2.8)

set(project friedrichdb)
project(${project} CXX)

set(CMAKE_CXX_STANDARD 11)

list(APPEND ${project}_HEADERS

        include/friedrichdb/data_types/object_id.hpp
        include/friedrichdb/data_types/ordering.h
        include/friedrichdb/data_types/time.hpp
        include/friedrichdb/data_types/timestamp.hpp

        include/friedrichdb/view/boolean.hpp
        include/friedrichdb/view/double_tt.hpp
        include/friedrichdb/view/object_id.hpp
        include/friedrichdb/view/positive_integer.hpp
        include/friedrichdb/view/view_t.hpp

        include/friedrichdb/abstract_database.hpp
        include/friedrichdb/composite_key.hpp
        include/friedrichdb/database.hpp
        include/friedrichdb/fake_file_storage.hpp
        include/friedrichdb/schema.hpp
        include/friedrichdb/table.hpp
        include/friedrichdb/tuple_t.hpp
        include/friedrichdb/type.hpp
        include/friedrichdb/storage.hpp
        include/friedrichdb/error.hpp
        include/friedrichdb/meta_data_t.hpp
        include/friedrichdb/field_t.hpp
)

list(APPEND ${project}_SOURCES

        data_types/object_id.cpp
        data_types/time.cpp
        data_types/timestamp.cpp

        composite_key.cpp
        database.cpp
        field_t.cpp
        schema.cpp
        storage.cpp
        table.cpp
        tuple_t.cpp
        type.cpp
)

add_library(${project} ${${project}_HEADERS} ${${project}_SOURCES})
set_property(TARGET ${project} PROPERTY EXPORT_NAME ${project})
target_include_directories(${project} PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include")