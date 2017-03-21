cmake_minimum_required(VERSION 3.6)
project(Lab8)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        sort_functions.c
        sort_functions.h
        sort_main.c)

add_executable(Lab8 ${SOURCE_FILES})