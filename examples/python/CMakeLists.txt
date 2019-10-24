cmake_minimum_required(VERSION 3.0)

set(project python_exampla)

project(${project} CXX)

include_directories(../friedrichdb/include)
set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES main.cpp)

add_executable(${project} ${SOURCE_FILES})
target_link_libraries(${PROJECT_NAME} friedrichdb)