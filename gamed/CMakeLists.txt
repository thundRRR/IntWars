file(GLOB src *.cpp)

set (CMAKE_CXX_FLAGS "-g -std=c++11")

include_directories(../dep/include ../dep/include/intlib)
add_executable(intwars ${src})
target_link_libraries(intwars enet intlib)