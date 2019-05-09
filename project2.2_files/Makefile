# A Sample Makefile

SRCS 		= subway_portal.cpp subway_station.cpp subway_system.cpp _hash_item.cpp hash_table.cpp gps.cpp 
OBJS       := $(patsubst %.cpp, %.o, $(SRCS))  
EXEC       := project2 
CXX        := /usr/bin/g++
CXXFLAGS   += -Wall -g -std=c++11  -no-pie -Iincludes 
$(EXEC): $(OBJS) main.o subway_route.o
	$(CXX) $(CXXFLAGS)  -o $@  $(OBJS) main.o subway_route.o

.PHONY: clean cleanall
cleanall: clean
	$(RM) $(EXEC)

clean:
	$(RM) $(OBJS)




