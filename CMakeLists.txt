cmake_minimum_required(VERSION 3.24)
project(OOP_lab1)

set(CMAKE_CXX_STANDARD 17)

add_executable(OOP_lab1 main.cpp
        menu.cpp
        menu.h
        struct.cpp
        struct.h
        individual.cpp
        individual.h)
