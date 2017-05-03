cmake_minimum_required(VERSION 3.6)
project(9_Interpreter_PhaseB)

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
        PT.cpp
        PT.h
        String.h)

add_executable(9_Interpreter_PhaseB ${SOURCE_FILES})