cmake_minimum_required(VERSION 3.10)
project(example1)

set(CMAKE_CXX_STANDARD 11)

link_libraries(pthread)

add_executable(example1 main.cpp)

