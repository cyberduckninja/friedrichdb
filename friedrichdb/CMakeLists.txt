cmake_minimum_required(VERSION 2.8)

set(project friedrichdb)
project(${project} CXX)

set(CMAKE_CXX_STANDARD 11)

list(APPEND ${project}_HEADERS

        include/friedrichdb/data_types/object_id.hpp
        include/friedrichdb/data_types/ordering.h
        include/friedrichdb/data_types/time.hpp
        include/friedrichdb/data_types/timestamp.hpp

        include/friedrichdb/index/hash_index.hpp
        include/friedrichdb/index/unique_hash_index.hpp

        include/friedrichdb/objects/boolean.hpp
        include/friedrichdb/objects/double_tt.hpp
        include/friedrichdb/objects/object_id.hpp
        include/friedrichdb/objects/positive_integer.hpp
        include/friedrichdb/objects/view_t.hpp

        include/friedrichdb/abstract_table.hpp
        include/friedrichdb/composite_key.hpp
        include/friedrichdb/database.hpp
        include/friedrichdb/fake_file_storage.hpp
        include/friedrichdb/schema.hpp
        include/friedrichdb/in-memory/in_memory_database.hpp
        include/friedrichdb/tuple_t.hpp
        include/friedrichdb/type.hpp
        include/friedrichdb/storage.hpp
        include/friedrichdb/meta_data_t.hpp
        include/friedrichdb/field_t.hpp
        include/friedrichdb/abstract_index.hpp
        include/friedrichdb/abstract_database.hpp
        include/friedrichdb/in-memory/table.hpp
        include/friedrichdb/in-memory/part_manager.hpp

)

list(APPEND ${project}_SOURCES
        abstract_index.cpp
        abstract_database.cpp
        data_types/object_id.cpp
        data_types/time.cpp
        data_types/timestamp.cpp
        in-memory/table.cpp
        in-memory/in_memory_database.cpp
        database.cpp
        composite_key.cpp
        field_t.cpp
        schema.cpp
        storage.cpp
        tuple_t.cpp
        type.cpp
)

add_library(${project} ${${project}_HEADERS} ${${project}_SOURCES} )
set_property(TARGET ${project} PROPERTY EXPORT_NAME ${project})
target_include_directories(${project} PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include")