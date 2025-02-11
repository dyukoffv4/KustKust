#include "source/sudoku/settable.hpp"

/// @class SetTable

void SetTable::clear() {
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            data[i][j].clear();
        }
    }
}
