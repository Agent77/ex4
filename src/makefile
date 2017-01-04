
all: server client

# Put here all the common files which are being used both in client and server
COMMON_SOURCES = BFS.cpp Node.cpp Clock.cpp Coordinate.cpp Point.cpp Graph.cpp Grid.cpp City.cpp Driver.cpp LuxuryCab.cpp StandardCab.cpp Passenger.cpp Searchable.cpp Taxi.cpp TaxiCenter.cpp Trip.cpp sockets/Udp.cpp sockets/Socket.cpp

server:
	g++ -std=c++0x Server.cpp $(COMMON_SOURCES) -lboost_serialization -I. -o server.out
# (for example)
client:
	g++ -std=c++0x DriverClient.cpp $(COMMON_SOURCES) -lboost_serialization -I. -o client.out
