cmake_minimum_required(VERSION 3.15)

project(friedrich_db CXX)

set(CMAKE_CXX_STANDARD 17 CACHE STRING "C++ version selection")
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(${PROJECT_NAME}_headers
        wrapper/convert.hpp
        wrapper/wrapper_database.hpp
        wrapper/wrapper_document.hpp
        wrapper/wrapper_client.hpp
        wrapper/wrapper_collection.hpp

)

set(${PROJECT_NAME}_sources
        main.cpp
        wrapper/convert.cpp
        wrapper/wrapper_database.cpp
        wrapper/wrapper_document.cpp
        wrapper/wrapper_client.cpp
        wrapper/wrapper_collection.cpp
)

include_directories(${PROJECT_SOURCE_DIR}

)

pybind11_add_module(${PROJECT_NAME}  ${${PROJECT_NAME}_sources} ${${PROJECT_NAME}_headers} )

target_link_libraries(
        ${PROJECT_NAME}
        PRIVATE
        friedrich
        ${CONAN_LIBS}
)

set_target_properties(${PROJECT_NAME} PROPERTIES CXX_VISIBILITY_PRESET "hidden")
