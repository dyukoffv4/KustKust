cmake_minimum_required(VERSION 3.16)
project(SudokuSolver VERSION 1.0.0 LANGUAGES C CXX)

find_package(PkgConfig REQUIRED)

pkg_check_modules(GTKMM REQUIRED gtkmm-4.0)

include_directories(${GTKMM_INCLUDE_DIRS})
link_directories(${GTKMM_LIBRARY_DIRS})
add_definitions(${GTKMM_CFLAGS_OTHER})

include_directories(${CMAKE_SOURCE_DIR})

add_executable(sudoku-solver source/main.cpp source/utilities/sudoku.cpp source/widgets/mapcell.cpp)
target_link_libraries(sudoku-solver ${GTKMM_LIBRARIES})