# A Sample Makefile
#
SRCS 		= subway_portal.cpp subway_station.cpp subway_system.cpp _hash_item.cpp hash_table.cpp gps.cpp 
OBJS       := $(patsubst %.cpp, %.o, $(SRCS))  
EXEC       := project2 
CXX        := /usr/bin/g++
CXXFLAGS   += -Wall -g -std=c++11  -no-pie -Iincludes -fsanitize=address,undefined

$(EXEC): $(OBJS) main.o subway_route.o
	@echo 'building.. executable'
	$(CXX) $(CXXFLAGS)  -o $@  $^
	@echo 'Project ready!'

%.o: %.cpp %.h
	@echo 'building object -> $@ ...'
	$(CXX) $(CXXFLAGS) -c $<
	@echo 'Success!'

listall:
	./project2 subwaydata_newstationnames.csv listall_cmmd


.PHONY: clean cleanall

cleanall: clean
	$(RM) $(EXEC)

clean:
	$(RM) $(OBJS)




