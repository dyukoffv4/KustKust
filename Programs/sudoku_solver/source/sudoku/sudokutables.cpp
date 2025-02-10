#include "source/sudoku/sudokutables.hpp"

/// @class SudokuTable

refvector<short> SudokuTable::cget(const int& x) {
    if (x < 0 || x > 8) throw std::out_of_range("Out of bounds!");
    refvector<short> result;
    for (int y = 0; y < 9; y++) result.push_back(data[y][x]);
    return result;
}

refvector<short> SudokuTable::rget(const int& y) {
    if (y < 0 || y > 8) throw std::out_of_range("Out of bounds!");
    refvector<short> result;
    for (int x = 0; x < 9; x++) result.push_back(data[y][x]);
    return result;
}

refvector<short> SudokuTable::qget(const int& y, const int& x) {
    if (x < 0 || x > 8 || y < 0 || y > 8) throw std::out_of_range("Out of bounds!");
    refvector<short> result;
    for (int i = y - y % 3; i < y - y % 3 + 3; i++) {
        for (int j = x - x % 3; j < x - x % 3 + 3; j++) {
            result.push_back(data[i][j]);
        }
    }
    return result;
}

/// @class SetSudokuTable

void SetSudokuTable::clear() {
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            data[i][j].clear();
        }
    }
}
