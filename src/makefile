all: server client
server: BFS.o Node.o Coordinate.o Point.o Graph.o Grid.o City.o Driver.o GameFlow.o LuxuryCab.o StandardCab.o Passenger.o Searchable.o Taxi.o TaxiCenterServer.o TaxiCenter.o Trip.o sockets/Udp.o sockets/Socket.o
	g++ -o server BFS.o Node.o Coordinate.o Point.o Graph.o Grid.o City.o Driver.o GameFlow.o LuxuryCab.o StandardCab.o Passenger.o Searchable.o Taxi.o TaxiCenterServer.o TaxiCenter.o Trip.o sockets/Udp.o sockets/Socket.o

client: BFS.o Node.o Coordinate.o Point.o Graph.o Grid.o City.o DriverClient.o Driver.o GameFlow.o LuxuryCab.o StandardCab.o Passenger.o TaxiCenter.o Searchable.o Taxi.o Trip.o sockets/Udp.o sockets/Socket.o
	g++ -o client BFS.o Node.o Coordinate.o Point.o Graph.o Grid.o City.o DriverClient.o Driver.o GameFlow.o LuxuryCab.o StandardCab.o Passenger.o TaxiCenter.o Searchable.o Taxi.o Trip.o sockets/Udp.o sockets/Socket.o

BFS.o: BFS.cpp BFS.h
	g++ -c BFS.cpp

Node.o: Node.cpp Node.h
	g++ -c Node.cpp

Coordinate.o: Coordinate.cpp Coordinate.h
	g++ -c Coordinate.cpp

Point.o: Point.cpp Point.h
	g++ -c Point.cpp

Graph.o: Graph.cpp Graph.h
	g++ -c Graph.cpp

Grid.o: Grid.cpp Grid.h
	g++ -c Grid.cpp

City.o: City.cpp City.h
	g++ -c City.cpp

Driver.o: Driver.cpp Driver.h
	g++ -c Driver.cpp

GameFlow.o: GameFlow.cpp GameFlow.h
	g++ -c GameFlow.cpp

LuxuryCab.o: LuxuryCab.cpp LuxuryCab.h
	g++ -c LuxuryCab.cpp

StandardCab.o: StandardCab.cpp StandardCab.h
	g++ -c StandardCab.cpp

Passenger.o: Passenger.cpp Passenger.h
	g++ -c Passenger.cpp

Searchable.o: Searchable.cpp Searchable.h
	g++ -c Searchable.cpp

Taxi.o: Taxi.cpp Taxi.h
	g++ -c Taxi.cpp

TaxiCenter.o: TaxiCenter.cpp TaxiCenter.h
	g++ -c TaxiCenter.cpp

Trip.o: Trip.cpp Trip.h
	g++ -c Trip.cpp

Socket.o: Socket.cpp Socket.h
	g++ -c Socket.cpp

src/Udp.o: Udp.cpp Udp.h
	g++ -c Udp.cpp

DriverClient.o: DriverClient.cpp DriverClient.h
	g++ -c DriverClient.cpp
