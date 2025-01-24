#include "sudoku.hpp"


Sudoku::Sudoku() {
    needed_q = needed_c = needed_r = setmap(9, {1, 2, 3, 4, 5, 6, 7, 8, 9});
    ddata = map(9);
    for (auto &i : ddata) i = row(9, 0);
}

bool Sudoku::setdata(const map& data) {
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

Sudoku::map Sudoku::getdata() {
    return ddata;
}

bool Sudoku::set(const int& row, const int& col, const int& val) {
    if (row < 0 || row > 8 || col < 0 || col > 9) throw std::out_of_range("Range out of bounds");
    if (val < 0 || val > 9) throw std::invalid_argument("Unsupported value for sudoku");

    std::set<int> &set_r = needed_r[row], &set_c = needed_c[col], &set_q = needed_q[row / 3 * 3 + col / 3];

    if (ddata[row][col] != 0) {
        set_r.insert(ddata[row][col]);
        set_c.insert(ddata[row][col]);
        set_q.insert(ddata[row][col]);
    }

    if (val != 0) {
        if (!set_r.count(val) || !set_c.count(val) || !set_q.count(val)) return false;
        set_r.erase(val);
        set_c.erase(val);
        set_q.erase(val);
    }
    
    ddata[row][col] = val;

    return true;
}

int Sudoku::get(const int& row, const int& col) {
    if (row < 0 || row > 8 || col < 0 || col > 9) throw std::out_of_range("Range out of bounds");
    return ddata[row][col];
}

bool Sudoku::solve() {
    std::set<int> rows, cols;
    int irow, icol, open;

    for (int tile = 0; tile < 9; tile++) {
        for (auto &i : needed_q[tile]) {
            for (int r = tile - tile % 3; r < tile - tile % 3 + 3; r++) {
                if (needed_r[r].count(i)) rows.insert(r);
            }
            for (int c = tile % 3 * 3; c < tile % 3 * 3 + 3; c++) {
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

    for (auto& r : needed_r) if (!r.empty()) return false;
    return true;
}

bool Sudoku::solve(map& table) {
    if (!solve()) return false;
    table = ddata;
    return true;
}

void Sudoku::clear() {
    needed_q = needed_c = needed_r = setmap(9, {1, 2, 3, 4, 5, 6, 7, 8, 9});
    for (auto &i : ddata) for (auto &j : i) j = 0;
}
