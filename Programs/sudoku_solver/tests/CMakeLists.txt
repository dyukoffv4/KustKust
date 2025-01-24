cmake_minimum_required(VERSION 3.16)
project(Tests VERSION 1.0.0 LANGUAGES C CXX)

include_directories(${CMAKE_SOURCE_DIR}/..)

add_executable(sudoku_test source/sudoku_test.cpp)