cmake_minimum_required(VERSION 3.16)
project(SudokuSolver VERSION 1.0.0 LANGUAGES C CXX)

find_package(PkgConfig REQUIRED)

pkg_check_modules(GTKMM REQUIRED gtkmm-4.0)

include_directories(${GTKMM_INCLUDE_DIRS})
link_directories(${GTKMM_LIBRARY_DIRS})
add_definitions(${GTKMM_CFLAGS_OTHER})

include_directories(${CMAKE_SOURCE_DIR})

add_library(sudoku source/sudoku/table.cpp source/sudoku/algs.cpp)
add_executable(sudoku-solver source/main.cpp source/widgets/mapcell.cpp source/widgets/gamemap.cpp)

target_link_libraries(sudoku-solver ${GTKMM_LIBRARIES})
target_link_libraries(sudoku-solver sudoku)