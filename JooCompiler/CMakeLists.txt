cmake_minimum_required(VERSION 3.6)
project(joo1wCompiler)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp Automata.h Automata.cpp)
add_executable(joo1wCompiler ${SOURCE_FILES})