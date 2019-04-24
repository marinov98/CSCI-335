# Makefile for project 2

CXX 		:= g++
CXXFLAGS	:= $(CXXFLAGS) -std=c++11 -Wall 
CPPS 		:= subway_portal.cpp subway_route.cpp subway_station.cpp subway_system.cpp
OBJS 		:= $(patsubst %.cpp, %.o, $(CPPS)) main.o
EXEC 		:= main

$(EXEC): $(OBJS)
	@echo 'building executable...'
	$(CXX) -o $@ $^

main.o: main.o.in
	cp -f $< $@

%.o: %.cpp %.h
	@echo 'building object => $@'
	$(CXX) $(CXXFLAGS) -c $<

debug: CXXFLAGS:=$(CXXFLAGS) -g -fsanitize=address,undefined

debug: main

.PHONY: clean cleanall 

cleanall:
	@echo 'removing all objects and executables...'
	$(RM) $(EXEC) $(OBJS)

clean:
	@echo 'removing executable and objects without main.o...'
	$(RM) $(EXEC) subway_portal.o subway_route.o subway_station.o subway_system.o

run:
	./main