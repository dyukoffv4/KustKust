#pragma once

#include "source/sudoku/table.hpp"
#include <set>

struct point {
    int y;
    int x;
    int v;
};

class Solver {
public:
    Solver();

    void load(std::istream& stream);
    void print(std::ostream& stream);
    void clear();

    bool solve();

protected:
    Table<short> data;
    Table<std::set<short>> set_data;

    point last_hero_square(int index);
};
