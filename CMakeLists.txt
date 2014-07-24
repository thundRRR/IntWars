cmake_minimum_required (VERSION 2.6)

IF(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
  SET(CMAKE_CXX_FLAGS "-g -std=c++11 -pedantic")
ELSEIF(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
  SET(CMAKE_CXX_FLAGS "/EHsc") #So it doesn't constantly throw warnings
ELSEIF(CMAKE_CXX_COMPILER_ID STREQUAL "Intel")
  IF(WIN32)
    SET(CMAKE_CXX_FLAGS "/Qstd=c++11")
  ELSE()
    SET(CMAKE_CXX_FLAGS "-std=c++11")
  ENDIF()
ELSEIF(CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
  SET(CMAKE_CXX_FLAGS "-std=c++11")
ENDIF()

IF(WIN32)
  LINK_LIBRARIES(ws2_32)
  LINK_LIBRARIES(winmm)
ENDIF()
project (IntWars)

add_subdirectory(dep)
add_subdirectory(gamed)
