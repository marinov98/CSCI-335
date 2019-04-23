CXXFLAGS=-std=c++11 -Wall -fPIC
#export CXXFLAGS="$(CXXFLAGS) -fPIC"

main: main.o subway_system.o subway_route.o subway_station.o subway_portal.o
	g++ -o main main.o subway_portal.o subway_route.o subway_station.o subway_system.o

subway_route.o: subway_route.cpp subway_route.h
	g++ $(CXXFLAGS) -c subway_route.cpp

subway_portal.o: subway_portal.cpp subway_portal.h
	g++ $(CXXFLAGS) -c subway_portal.cpp

subway_station.o: subway_station.h subway_station.cpp
	g++ $(CXXFLAGS) -c subway_station.cpp

subway_system.o: subway_system.h subway_system.cpp
	g++ $(CXXFLAGS) -c subway_system.cpp

debug: CXXFLAGS:=$(CXXFLAGS) -g

debug: main

clean:
	rm -f main subway_route.o subway_portal.o subway_system.o subway_station.o

run:
	./main