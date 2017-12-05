cmake_minimum_required(VERSION 3.6)
project(Project8)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp Input.cpp Parse.h String.h BST.h ExpTree.h ExpTree.cpp Project8.cpp Project8.h)
add_executable(Project8 ${SOURCE_FILES} main.cpp)