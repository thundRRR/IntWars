cmake_minimum_required (VERSION 2.6)

SET (CMAKE_CXX_COMPILER g++)
SET (CMAKE_CXX_FLAGS "-g -std=c++11")

IF(WIN32)
  LINK_LIBRARIES(ws2_32)
  LINK_LIBRARIES(winmm)
ENDIF()
project (IntWars)

add_subdirectory(dep)
add_subdirectory(gamed)
