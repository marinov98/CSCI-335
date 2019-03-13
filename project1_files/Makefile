# A Sample Makefile
# If you wish to use a Makefile in your project, you will most likely
# need to edit this one. 
# For example, if you do not have a file named utilities.h or one
# named utilities.cpp, just remove them from this Makefile.
# If you use a file named dsexceptions.h, as the book does, and avl.cpp
# depends on it, then add its name to the line for avl.o below.

SRCS       := tree.cpp tree_collection.cpp tree_species.cpp utilities.cpp
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
# avl.o:             AvlTree.h tree.h utilities.h
tree_collection.o: tree.h tree_species.h
tree.o:            tree.h 
tree_species.o:    tree_species.h
