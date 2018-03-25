cmake_minimum_required(VERSION 3.8)
project(exact_cover)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        data.cpp
        data.h
        solver.cpp
        solver.h
        utils.h)

add_executable(exact_cover ${SOURCE_FILES} main.cpp)

add_executable(sudoku ${SOURCE_FILES} sudoku.cpp sudoku.h)