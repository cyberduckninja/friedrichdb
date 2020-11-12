cmake_minimum_required(VERSION 3.0)

project(friedrichdb_test_shm CXX)


include_directories(../header)

list(APPEND ${PROJECT_NAME}_HEADERS

)

list(APPEND ${PROJECT_NAME}_SOURCES


)



add_executable(${PROJECT_NAME} main.cpp ${${PROJECT_NAME}_HEADERS} ${${PROJECT_NAME}_SOURCES})
