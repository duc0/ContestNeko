cmake_minimum_required(VERSION 2.8.4)
project(jhelper-example-project)

add_executable(output output/main.cpp)
add_executable(testrunner testrunner/main.cpp)
file(GLOB TASKS "tasks/*.cpp")
file(GLOB_RECURSE HEADERS "library/*.hpp" )

include_directories(library)
include_directories(library/Number)
include_directories(library/Combinatorics)
include_directories(library/Iterable)
include_directories(library/DataStructures)
include_directories(library/Algorithms)
include_directories(library/String)

ADD_DEFINITIONS(-std=c++11)

add_executable(test ${TASKS} ${HEADERS})
