cmake_minimum_required(VERSION 3.0)

project(friedrich CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED YES)
set(CMAKE_CXX_EXTENSIONS OFF)

option(CONAN_EXPERIMENTAL_INCLUDE "CONAN EXPERIMENT INCLUDE" ON)

if ((CMAKE_CXX_COMPILER_ID MATCHES "GNU") OR (CMAKE_CXX_COMPILER_ID MATCHES "Clang"))
    add_compile_options(
            -Wall
            -Wextra
            -Wpedantic

            -Wcast-align
            -Wcast-qual
            -Wconversion
            -Wctor-dtor-privacy
            -Wenum-compare
            -Wfloat-equal
            -Wnon-virtual-dtor
            -Wold-style-cast
            -Woverloaded-virtual
            -Wredundant-decls
            -Wsign-conversion
            -Wsign-promo
    )
elseif (CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
    add_compile_options(/W4 /WX)
endif ()

#############################################################################################
#conan

if (NOT EXISTS "${CMAKE_BINARY_DIR}/conan.cmake")
    message(STATUS "Downloading conan.cmake from https://github.com/conan-io/cmake-conan")
    file(DOWNLOAD "https://raw.githubusercontent.com/conan-io/cmake-conan/v0.15/conan.cmake" "${CMAKE_BINARY_DIR}/conan.cmake")
endif ()

include(${CMAKE_BINARY_DIR}/conan.cmake)

if (CONAN_EXPERIMENTAL_INCLUDE)
    set(CONAN_SYSTEM_INCLUDES "On")
endif ()

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
if (CCACHE_FOUND)
    message(STATUS "Enabling ccache")
    set_property(GLOBAL PROPERTY RULE_LAUNCH_COMPILE ccache)
    set_property(GLOBAL PROPERTY RULE_LAUNCH_LINK ccache)
endif (CCACHE_FOUND)

#ccahe
#############################################################################################

include_directories(header)


list(APPEND ${PROJECT_NAME}_HEADERS

        #header/friedrichdb/core/field.hpp
        #header/friedrichdb/core/number.hpp
        #header/friedrichdb/core/options.hpp
        #header/friedrichdb/core/schema.hpp
        #header/friedrichdb/core/type.hpp
        header/friedrichdb/core/collection.hpp
        header/friedrichdb/core/database.hpp
        header/friedrichdb/core/document.hpp

        #header/friedrichdb/functions/join.hpp
        #header/friedrichdb/functions/update.hpp

        #header/friedrichdb/in-memory/database.hpp

        #header/friedrichdb/shared_memory/shm.hpp
        #header/friedrichdb/shared_memory/node_allocator.hpp

)

list(APPEND ${PROJECT_NAME}_SOURCES
        #source/friedrichdb/core/dict.cpp
        source/friedrichdb/core/collection.cpp
        source/friedrichdb/core/database.cpp
        source/friedrichdb/core/document.cpp
)

SET(PYTHON_EXECUTABLE python3)
#find_package(pybind11 REQUIRED)
find_package(Python3 COMPONENTS Interpreter Development)
include_directories(${Python3_INCLUDE_DIRS})

add_subdirectory(test)

add_library(${PROJECT_NAME} ${${PROJECT_NAME}_HEADERS} ${${PROJECT_NAME}_SOURCES})
#set_property(TARGET ${project} PROPERTY EXPORT_NAME ${project})
set_property(TARGET ${PROJECT_NAME} PROPERTY POSITION_INDEPENDENT_CODE ON)
target_include_directories(${PROJECT_NAME} PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/header")
target_link_libraries(${PROJECT_NAME} PRIVATE ${CONAN})
add_subdirectory(examples)

add_subdirectory(integration)