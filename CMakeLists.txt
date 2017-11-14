cmake_minimum_required(VERSION 3.6)
project(Project8)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp Input.cpp Parse.h main.cpp)
add_executable(Project8 ${SOURCE_FILES} main.cpp)