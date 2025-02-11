#pragma once

#include "source/sudoku/table.hpp"
#include <set>

class SetTable : public Table<std::set<short>> {
public:
    void clear();
};
