#pragma once

#include "source/sudoku/table.hpp"
#include <set>

template<class T>
using refvector = std::vector<std::reference_wrapper<T>>;

class SudokuTable : public Table<short> {
public:
    refvector<short> cget(const int& x);
    refvector<short> rget(const int& y);
    refvector<short> qget(const int& y, const int& x);
};

class SetSudokuTable : public Table<std::set<short>> {
public:
    void clear();
};
