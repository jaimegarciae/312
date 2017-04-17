cmake_minimum_required(VERSION 3.6)
project(8__Interpreter)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        DB.cpp
        DB.h
        ET.cpp
        ET.h
        handler.cpp
        handler.h
        Input.cpp
        main.cpp
        Parse.h
        String.h)

add_executable(8__Interpreter ${SOURCE_FILES})