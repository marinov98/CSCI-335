cmake_minimum_required(VERSION 3.13)
project(project2_2_files)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(project2_2_files
        _hash_item.cpp
        _hash_item.h
        gps.cpp
        gps.h
        hash_table.cpp
        hash_table.h
        subway_portal.cpp
        subway_portal.h
        subway_route.h
        subway_route.cpp
        subway_station.cpp
        subway_station.h
        disjoint_set.cpp
        disjoint_set.h
        subway_system.cpp
        subway_system.h)
