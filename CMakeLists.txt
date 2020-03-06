cmake_minimum_required(VERSION 3.0)

set(project friedrichdb)
project(${project} CXX)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED YES)
set(CMAKE_CXX_EXTENSIONS OFF)

add_compile_options(
        -v

        -Wall
        -Wextra
        -Wpedantic

        -Wcast-align
        #-Wcast-qual
        #-Wconversion
        -Wctor-dtor-privacy
        -Wenum-compare
        #-Wfloat-equal
        -Wnon-virtual-dtor
        #-Wold-style-cast
        -Woverloaded-virtual
        -Wredundant-decls
        #-Wsign-conversion
        -Wsign-promo
)

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

include_directories(header)


list(APPEND ${PROJECT_NAME}_HEADERS

        header/friedrichdb/core/basic_field.hpp
        header/friedrichdb/core/collection.hpp
        header/friedrichdb/core/options.hpp
        header/friedrichdb/core/schema.hpp
        header/friedrichdb/core/type.hpp

        header/friedrichdb/in-memory/database.hpp

        header/friedrichdb/shared_memory/shm.hpp
        header/friedrichdb/shared_memory/node_allocator.hpp

)

list(APPEND ${PROJECT_NAME}_SOURCES
        sourcer/in-memory/in_memory_collection.cpp
        sourcer/in-memory/database.cpp
)

add_subdirectory(test)

add_library(${PROJECT_NAME} ${${project}_HEADERS} ${${project}_SOURCES} )
#set_property(TARGET ${project} PROPERTY EXPORT_NAME ${project})
target_include_directories(${PROJECT_NAME} PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/header")
target_link_libraries(${PROJECT_NAME} PRIVATE ${CONAN})
add_subdirectory(examples)