cmake_minimum_required(VERSION 3.3)
project(ac)

# To make clion see header files
include_directories("./automata/include")
# To make clion see source files - for unit tests
include_directories("./automata/src")
# To make clion see gtests header file - for unit tests
include_directories("./googletest/include")


set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
    automata/include/console.h
    automata/include/main.h
    automata/src/console.cpp
    automata/src/main.cpp
    automata/test/src/test.cpp
    automata/makefile
    makefile)

add_executable(ac ${SOURCE_FILES})