cmake_minimum_required(VERSION 3.6)
project(MyVector)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
        MyVector/main.cpp
        MyVector/MyIntVector.cpp
        MyVector/MyIntVector.hpp
        MyVector/MyVector.hpp
        )

add_executable(MyVector ${SOURCE_FILES})