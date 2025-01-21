#include "gamemap.hpp"


GameMap::GameMap() {
    set_column_spacing(5);
    set_row_spacing(5);

    cells = std::vector<std::vector<MapCell>>(9);
    for (auto &i : cells) i = std::vector<MapCell>(9);

    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) attach(cells[i][j], j, i);
        cells[2][i].set_margin_bottom(10);
        cells[5][i].set_margin_bottom(10);
        cells[i][2].set_margin_end(10);
        cells[i][5].set_margin_end(10);
    }

    bool success = false;
}

bool GameMap::setup() {
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            if (!sudoku.set(i, j, cells[i][j].get_value())) {
                sudoku.clear();
                return false;
            }
        }
    }
    return true;
}

bool GameMap::solve() {
    if (!(success = sudoku.solve())) sudoku.clear();
    return success;
}

void GameMap::print() {
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            cells[i][j].set_text(std::to_string(sudoku.get(i, j)));
        }
    }
}

void GameMap::clear() {
    sudoku.clear();
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            cells[i][j].set_text("");
        }
    }
}
