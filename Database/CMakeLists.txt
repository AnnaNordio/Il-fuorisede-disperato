cmake_minimum_required(VERSION 3.26)
project(Database)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(Database
        database.cpp
        database.h)
