cmake_minimum_required(VERSION 2.8)

set(project friedrichdb)
project(${project} CXX)

set(CMAKE_CXX_STANDARD 11)

list(APPEND ${project}_HEADERS

        header/friedrichdb/data_types/object_id.hpp
        header/friedrichdb/data_types/ordering.h
        header/friedrichdb/data_types/time.hpp
        header/friedrichdb/data_types/timestamp.hpp

        header/friedrichdb/in-memory/in_memory_database.hpp
        header/friedrichdb/in-memory/table.hpp
        header/friedrichdb/in-memory/part_manager.hpp

        header/friedrichdb/index/hash_index.hpp
        header/friedrichdb/index/unique_hash_index.hpp

        header/friedrichdb/objects/boolean.hpp
        header/friedrichdb/objects/double_tt.hpp
        header/friedrichdb/objects/object_id.hpp
        header/friedrichdb/objects/positive_integer.hpp
        header/friedrichdb/objects/view_t.hpp

        header/friedrichdb/abstract_table.hpp
        header/friedrichdb/composite_key.hpp
        header/friedrichdb/database.hpp
        header/friedrichdb/fake_file_storage.hpp
        header/friedrichdb/schema.hpp
        header/friedrichdb/tuple_t.hpp
        header/friedrichdb/type.hpp
        header/friedrichdb/storage.hpp
        #header/friedrichdb/transaction.hpp
        #header/friedrichdb/journal.hpp
        header/friedrichdb/meta_data_t.hpp
        #header/friedrichdb/query.hpp
        header/friedrichdb/field_t.hpp
        header/friedrichdb/abstract_index.hpp
        header/friedrichdb/abstract_database.hpp

)

list(APPEND ${project}_SOURCES
        sourcer/abstract_index.cpp
        sourcer/abstract_database.cpp
        sourcer/data_types/object_id.cpp
        sourcer/data_types/time.cpp
        sourcer/data_types/timestamp.cpp
        sourcer/in-memory/table.cpp
        sourcer/in-memory/in_memory_database.cpp
        sourcer/database.cpp
        sourcer/composite_key.cpp
        sourcer/field_t.cpp
        sourcer/schema.cpp
        sourcer/storage.cpp
        sourcer/tuple_t.cpp
        sourcer/type.cpp
)

add_library(${project} ${${project}_HEADERS} ${${project}_SOURCES})
set_property(TARGET ${project} PROPERTY EXPORT_NAME ${project})
target_include_directories(${project} PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/header")

#add_subdirectory(example)