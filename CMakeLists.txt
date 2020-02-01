cmake_minimum_required(VERSION 3.0)

set(project friedrichdb)
project(${project} CXX)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED YES)
set(CMAKE_CXX_EXTENSIONS OFF)

#############################################################################################
#conan

if(NOT EXISTS "${CMAKE_BINARY_DIR}/conan.cmake")
    message(STATUS "Downloading conan.cmake from https://github.com/conan-io/cmake-conan")
    file(DOWNLOAD "https://raw.githubusercontent.com/conan-io/cmake-conan/v0.14/conan.cmake" "${CMAKE_BINARY_DIR}/conan.cmake")
endif()

find_package(Python3 COMPONENTS Development)
include_directories(${Python3_INCLUDE_DIRS})

include(${CMAKE_BINARY_DIR}/conan.cmake)

conan_add_remote(NAME bincrafters INDEX 1 URL https://api.bintray.com/conan/bincrafters/public-conan)

conan_cmake_run(
        CONANFILE conanfile.txt
        BASIC_SETUP
        BUILD missing
        NO_OUTPUT_DIRS
)

#conan
#############################################################################################
#ccahe

find_program(CCACHE_FOUND ccache)
if(CCACHE_FOUND)
    message(STATUS "Enabling ccache")
    set_property(GLOBAL PROPERTY RULE_LAUNCH_COMPILE ccache)
    set_property(GLOBAL PROPERTY RULE_LAUNCH_LINK ccache)
endif(CCACHE_FOUND)

#ccahe
#############################################################################################

#add_definitions(-DRAPIDJSON_HAS_STDSTRING)

#add_definitions(-DRAPIDJSON_HAS_CXX11_RVALUE_REFS)

#include_directories(thirdparty/rapidjson/include)

list(APPEND ${PROJECT_NAME}_HEADERS

        header/friedrichdb/in-memory/in_memory_collection.hpp
        header/friedrichdb/in-memory/in_memory_database.hpp
        header/friedrichdb/in-memory/in_memory_table.hpp
        header/friedrichdb/tenser/tensor.hpp


        header/friedrichdb/abstract_collection.hpp
        header/friedrichdb/abstract_database.hpp
        header/friedrichdb/abstract_index.hpp
        header/friedrichdb/composite_key.h
        header/friedrichdb/controller.hpp
        header/friedrichdb/database.hpp
        header/friedrichdb/core/document.hpp
        header/friedrichdb/fake_file_storage.hpp
        header/friedrichdb/journal.hpp
        header/friedrichdb/operation.hpp
        header/friedrichdb/query.hpp
        header/friedrichdb/query_scheduler.hpp
        header/friedrichdb/serializable.hpp
        header/friedrichdb/storage.hpp
        header/friedrichdb/transaction.hpp



)

list(APPEND ${PROJECT_NAME}_SOURCES
        sourcer/abstract_database.cpp
        sourcer/in-memory/in_memory_collection.cpp
        sourcer/in-memory/in_memory_database.cpp
        sourcer/document.cpp
        sourcer/abstract_collection.cpp
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

add_subdirectory(test)

add_library(${PROJECT_NAME} ${${project}_HEADERS} ${${project}_SOURCES})
#set_property(TARGET ${project} PROPERTY EXPORT_NAME ${project})
target_include_directories(${PROJECT_NAME} PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/header")

add_subdirectory(examples)