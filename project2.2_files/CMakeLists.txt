cmake_minimum_required(VERSION 3.13)
project(project2_2_files)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS_DEBUG "-no-pie -Iincludes")

include_directories(.)

add_executable(project2
                main.o
                subway_route.o
                _hash_item.cpp _hash_item.h
                gps.cpp gps.h
                hash_table.cpp hash_table.h
                subway_station.cpp subway_station.h
                subway_portal.cpp subway_portal.h
                subway_system.cpp subway_system.h)
