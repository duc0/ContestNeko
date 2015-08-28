cmake_minimum_required(VERSION 3.3)
project(ProgrammingContest)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
    CPPProjects/main.cpp)

add_executable(ProgrammingContest ${SOURCE_FILES})