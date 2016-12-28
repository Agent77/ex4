cmake_minimum_required(VERSION 3.5)
project(ex4)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")
set(core_sockets src/sockets/Socket.cpp src/sockets/Udp.cpp)
set(SOURCE_FILES src/sockets/Udp.cpp src/sockets/Socket.cpp src/Driver.cpp src/BFS.cpp src/City.cpp src/Clock.cpp
        src/Coordinate.cpp src/Graph.cpp src/Grid.cpp
        src/LuxuryCab.cpp src/Node.cpp src/Passenger.cpp src/Point.cpp src/StandardCab.cpp src/Taxi.cpp src/TaxiCenter.cpp src/Trip.cpp)
set(BOOST_ROOT CACHE PATH "/Users/Tiki/ClionProjects/ex4/boost_1_62_0")
find_package(Boost 1.59.0 COMPONENTS serialization system)
add_library(sockets ${core_sockets})
add_executable(server src/Server.cpp ${SOURCE_FILES})
#add_executable(client src/DriverClient.cpp ${SOURCE_FILES})
target_link_libraries(server sockets)
#target_link_libraries(client sockets)
#target_link_libraries(client ${Boost_LIBRARIES} sockets)
target_link_libraries(server ${Boost_LIBRARIES} sockets)
INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIR})












