cmake_minimum_required(VERSION 3.6)
project(4__CRM)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        Invent.h
        main.cpp
        MyString.cpp
        MyString.h
        Project4.cpp
        test1.txt
        test2.txt
        test3.txt)

add_executable(4__CRM ${SOURCE_FILES})