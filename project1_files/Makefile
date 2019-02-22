# A Sample Makefile

SRCS       := tree.cpp tree_collection.cpp avl.cpp  tree_species.cpp utilities.cpp
OBJS       := $(patsubst %.cpp, %.o, $(SRCS))  main.o 
EXEC       := project1 
CXX        := /usr/bin/g++
CXXFLAGS     += -Wall -g

$(EXEC): $(OBJS)
	$(CXX) $(CXXFLAGS)  -o build/$@  $(OBJS)

.PHONY: clean cleanall
cleanall: clean
	$(RM) $(EXEC)

clean:
	$(RM) $(OBJS)

tree_species.h:    __tree_species.h
tree_collection.h: __tree_collection.h
avl.o:             avl.h tree.h utilities.h
tree_collection.o: tree.h tree_species.h
tree.o:            tree.h 
tree_species.o:    tree_species.h
