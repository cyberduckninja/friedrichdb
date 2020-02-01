cmake_minimum_required(VERSION 3.0)

set(project python_exampla)

project(${project} CXX)

set(SOURCE_FILES main.cpp)

add_executable(${project} ${SOURCE_FILES})
target_link_libraries(${PROJECT_NAME} friedrichdb)