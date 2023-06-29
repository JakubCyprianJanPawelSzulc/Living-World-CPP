cmake_minimum_required(VERSION 3.25)
project(Living_World_New)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(Living_World_New
        Virtual/Organism.cpp
        Virtual/Organism.h
        Virtual/Plant.cpp
        Virtual/Plant.h
        Living_World.cpp
        Utils/World.h Utils/World.cpp Utils/Position.cpp Utils/Position.h Virtual/Animal.cpp Virtual/Animal.h Plants/Grass.h Plants/Grass.cpp Plants/Dandelion.cpp Plants/Dandelion.h Plants/Toadstool.h Plants/Toadstool.cpp Animals/Sheep.cpp Animals/Wolf.cpp Animals/Wolf.h)
