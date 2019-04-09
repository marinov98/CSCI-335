cmake_minimum_required(VERSION 3.13)
project(project2_files)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(project2_files
        _hash_item.cpp
        _hash_item.h
        gps.cpp
        gps.h
        hash_table.cpp
        hash_table.h
        main.cpp)
