cmake_minimum_required(VERSION 3.16)
project(Tests VERSION 1.0.0 LANGUAGES C CXX)

set(SUDOKU ${CMAKE_SOURCE_DIR}/../source/sudoku)

include_directories(${CMAKE_SOURCE_DIR}/..)

add_executable(sudoku_test source/sudoku_test ${SUDOKU}/sudokutables.cpp ${SUDOKU}/algs.cpp)