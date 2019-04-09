CXXFLAGS=-std=c++11

main: main.o hash_table.o _hash_item.o gps.o
	g++ -o main main.o hash_table.o _hash_item.o gps.o

main.o: main.cpp _hash_item.h hash_table.cpp
	g++ $(CXXFLAGS) -c main.cpp

_hash_item.o: _hash_item.cpp _hash_item.h
	g++ $(CXXFLAGS) -c _hash_item.cpp

hash_table.o: hash_table.cpp hash_table.h
	g++ $(CXXFLAGS) -c hash_table.cpp

gps.o: gps.cpp gps.h
	g++ $(CXXFLAGS) -c gps.cpp

debug: CXXFLAGS:=$(CXXFLAGS) -g -fsanitize=address,undefined

debug: main

clean:
	rm -f main main.o _hash_item.o hash_table.o gps.o

run:
	./main

