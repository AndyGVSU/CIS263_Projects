cmake_minimum_required(VERSION 3.12)
project(HW05)

set(CMAKE_CXX_STANDARD 14)

add_executable(textsearch hw05_text.cpp WordSearch.cpp FileSystem.cpp)