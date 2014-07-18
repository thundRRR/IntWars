include_directories(include include/intlib)

file(GLOB enet_src src/enet/*.c)
file(GLOB intlib_src src/intlib/*.cpp)

add_library(enet ${enet_src})
add_library(intlib ${intlib_src})