cmake_minimum_required(VERSION 3.8)
project(EX1)

set(CMAKE_CXX_STANDARD 11)
set(SOURCE_FILES main.cpp SplayTree.cpp Trainer.cpp Gladiator.cpp
        ComodosDS.cpp library1.cpp utility.h splayTest.cpp SplitAndSortTree.h)

add_executable(EX1 ${SOURCE_FILES})
