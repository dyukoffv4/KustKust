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

    /// @brief Create map of allowed numbers at each tiles on square
    void square_allowed_create(tsa& allowed, const int& x, const int& y);
    /// @brief Find and fill all tiles where can be only one number
    bool square_solve_1(tsa& allowed, const int& x, const int& y);
    /// @brief Find and fill all tiles where can be only one number
    bool square_solve_2(tsa& allowed, const int& x, const int& y);
};
