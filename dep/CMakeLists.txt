include_directories(include include/intlib)
include_directories(../gamed/include include include/intlib include/raf)

file(GLOB enet_src src/enet/*.c)
file(GLOB intlib_src src/intlib/*.cpp)
file(GLOB raf_src src/raf/*.cpp)

add_library(enet ${enet_src})
add_library(intlib ${intlib_src})
add_library(raf ${raf_src})