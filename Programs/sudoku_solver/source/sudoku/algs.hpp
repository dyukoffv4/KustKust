#pragma once

#include "source/sudoku/sudokutables.hpp"

struct point {
    int y;
    int x;
    int v;
};

bool check_sudoku(SudokuTable& data);

bool init_sudoku_set(SetSudokuTable& set_data, SudokuTable& data);

point last_hero_square(SetSudokuTable& set_data, int qcol, int qrow);

bool solve_sudoku(SudokuTable& data, SetSudokuTable& set_data);
