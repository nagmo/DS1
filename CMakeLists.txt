cmake_minimum_required(VERSION 3.8)
project(EX1)

set(CMAKE_CXX_STANDARD 98)

file(GLOB HEADERS ./*.h)
set(SOURCE_FILES main.cpp ComodosDS.cpp Gladiator.cpp library1.cpp
            Trainer.cpp)

add_executable(EX1 ${SOURCE_FILES} ${HEADERS})
