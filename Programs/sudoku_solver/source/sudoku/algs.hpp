#pragma once

#include "source/sudoku/table.hpp"
#include <set>
#include <map>

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

    bool check_data(Table<short>& t_data);

    bool last_hero_square(const int& index);
};
