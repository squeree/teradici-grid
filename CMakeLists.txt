cmake_minimum_required(VERSION 3.16)
project(teradici-grid)

set(CMAKE_CXX_STANDARD 20)

add_executable (grid main.cpp Grid.cpp)

add_executable (grid-test test.cpp Grid.cpp)