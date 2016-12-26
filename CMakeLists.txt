cmake_minimum_required(VERSION 3.3)
project(practice6)

set(core_sockets src/sockets/Socket.cpp src/sockets/Udp.cpp src/sockets/Tcp.cpp)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

add_library(sockets ${core_sockets})


add_executable(server server.cpp)
add_executable(client client.cpp)

target_link_libraries(server sockets)
target_link_libraries(client sockets)