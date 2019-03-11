cmake_minimum_required(VERSION 3.13)
project(code_reading)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(code_reading
        contact.cpp
        contact.h
        contactlist.cpp
        contactlist.h
        name.cpp
        name.h
        main.cpp)
