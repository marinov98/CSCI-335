cmake_minimum_required(VERSION 3.13)
project(project1_files)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(project1_files
        __tree_collection.h
        __tree_species.h
        AvlTree.cpp
        AvlTree.h
        dsexceptions.h
        tree.cpp
        tree.h
        tree_collection.cpp
        tree_collection.h
        tree_species.cpp
        tree_species.h)
