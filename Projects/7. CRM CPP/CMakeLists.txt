cmake_minimum_required(VERSION 3.6)
project(7__CRM_CPP)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        Customer.h
        CustomerDB.cpp
        CustomerDB.h
        main.cpp
        MemHeap.cpp
        MemHeap.h
        Project7.cpp
        String.h
        test1.txt
        test2.txt
        test3.txt
        test4.txt)

add_executable(7__CRM_CPP ${SOURCE_FILES})