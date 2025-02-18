#pragma once

#include "source/sudoku/table.hpp"
#include <set>
#include <map>

class Solver {
public:
    Solver();

    void enter(std::istream& stream);
    void print(std::ostream& stream);

    short get(const int& x, const int& y) const;
    bool set(const int& x, const int& y, const short& v);

    void clear();
    bool solve();

    typedef std::map<int, std::set<short>> tsa;

protected:
    Table table;
    std::vector<std::set<short>> column_sets;
    std::vector<std::set<short>> string_sets;
    std::vector<std::set<short>> square_sets;

    void square_allowed_create(tsa& allowed, const int& x, const int& y);
    bool square_solve_1(tsa& allowed, const int& x, const int& y);
    bool square_solve_2(tsa& allowed, const int& x, const int& y);
};
