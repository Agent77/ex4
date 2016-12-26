cmake_minimum_required(VERSION 3.3)
project(practice6)

set(core_sockets src/sockets/Socket.cpp src/sockets/Udp.cpp src/sockets/Tcp.cpp)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

add_library(sockets ${core_sockets})

include_directories("/Users/Tiki/Downloads/boost_1_62_0")

set(BOOST_ROOT "/Users/Tiki/Downloads/boost_1_62_0")
set(Boost_Path "/Users/Tiki/Downloads/boost_1_62_0")

set(Boost_INCLUDE_DIR "${Boost_Path}/boost_1_62_0")
add_executable(server server.cpp)
add_executable(client client.cpp)

target_link_libraries(server sockets)
target_link_libraries(client sockets)