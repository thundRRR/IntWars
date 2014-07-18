cmake_minimum_required (VERSION 2.6)

SET (CMAKE_CXX_COMPILER g++)
set (CMAKE_CXX_FLAGS "-g -std=c++11")

project (Intwars)

add_subdirectory(dep)
add_subdirectory(gamed)
