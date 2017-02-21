cmake_minimum_required(VERSION 3.6)
project(Project2)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        main.cpp
        Makefile
        matrix-multiplication.pdf
        MatrixMultiply.h
        Project2.cpp)

add_executable(Project2 ${SOURCE_FILES})