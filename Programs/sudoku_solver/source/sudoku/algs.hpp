#pragma once

#include "source/sudoku/settable.hpp"

typedef Table<short> ShortTable;

struct point {
    int y;
    int x;
    int v;
};

bool check_sudoku(ShortTable& data);

bool init_sudoku_set(SetTable& set_data, ShortTable& data);

point last_hero_square(SetTable& set_data, int qcol, int qrow);

bool solve_sudoku(ShortTable& data, SetTable& set_data);
