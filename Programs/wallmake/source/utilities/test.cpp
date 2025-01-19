#include "test.hpp"
#include <iostream>


Sudoku::Sudoku() {
    needed_q = needed_c = needed_r = setmap(9, {1, 2, 3, 4, 5, 6, 7, 8, 9});
    ddata = map(9);
    for (auto &i : ddata) i = row(9, 0);
}

bool Sudoku::load(const map& data) {
    if (data.size() != 9) return false;
    for (auto &i : data) if (i.size() != 9) return false;

    std::set<int> *set_r, *set_c, *set_q;
    int tile;

    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            tile = data.at(i).at(j);

            if (tile < 0 || tile > 9) {
                needed_q = needed_c = needed_r = setmap(9, {1, 2, 3, 4, 5, 6, 7, 8, 9});
                return false;
            }

            if (tile = data.at(i).at(j)) {
                set_r = &needed_r[i];
                set_c = &needed_c[j];
                set_q = &needed_q[i / 3 * 3 + j / 3];
                
                if (!set_r->count(tile) || !set_c->count(tile) || !set_q->count(tile)) {
                    needed_q = needed_c = needed_r = setmap(9, {1, 2, 3, 4, 5, 6, 7, 8, 9});
                    return false;
                }
                
                set_r->erase(tile);
                set_c->erase(tile);
                set_q->erase(tile);
            }
        }
    }

    ddata = data;

    return true;
}

Sudoku::map Sudoku::data() {
    return ddata;
}

bool Sudoku::solve() {
    std::set<int> rows, cols;
    int irow, icol, open;

    for (int tile = 0; tile < 9; tile++) {
        for (auto &i : needed_q[tile]) {
            for (int r = tile / 3; r < tile / 3 + 2; r++) {
                if (needed_r[r].count(i)) rows.insert(r);
            }
            for (int c = tile % 3 * 3; c < tile % 3 * 3 + 2; c++) {
                if (needed_c[c].count(i)) cols.insert(c);
            }

            open = rows.size() * cols.size();
            for (auto &r : rows) {
                for (auto &c : cols) {
                    if (ddata[r][c]) open--;
                    else {
                        irow = r;
                        icol = c;
                    }
                }
            }

            rows.clear();
            cols.clear();

            if (open == 0) return false;
            if (open == 1) {
                ddata[irow][icol] = i;
                needed_r[irow].erase(i);
                needed_c[icol].erase(i);
                needed_q[tile].erase(i);
                tile = -1;
                break;
            }
        }
    }

    return true;
}

bool Sudoku::solve(map& table) {
    if (!solve()) return false;
    table = ddata;
    return true;
}


int main(int argc, char* argv[]) {
    std::cout << "Enter sudoku template. Print zero in empty places.\n\n";

    Sudoku::map table(9, Sudoku::row(9));
    for (auto& i : table) for (auto& j : i) { std::cin >> j; if (j < 0 || j > 9) return 1; }

    Sudoku sudoku;
    if (!sudoku.load(table)) return 2;
    
    std::cout << "\nStart calculating.\n\n";
    if (!sudoku.solve(table)) return 3;

    std::cout << "Result.\n\n";
    for (auto& i : table) {
        for (auto& j : i) std::cout << j << ' ';
        std::cout << '\n';
    }

    return 0;
}
