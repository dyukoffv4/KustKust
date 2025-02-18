#include "source/sudoku/algs.hpp"

Solver::Solver() {
    for (int i = 0; i < 9; i++) {
        column_sets.push_back({1, 2, 3, 4, 5, 6, 7, 8, 9});
        string_sets.push_back({1, 2, 3, 4, 5, 6, 7, 8, 9});
        square_sets.push_back({1, 2, 3, 4, 5, 6, 7, 8, 9});
    }
}

void Solver::enter(std::istream& stream) {
    Solver solver;
    stream >> solver.table;

    std::set<short> block_set;
    for (int i = 0; i < 9; i++) {
        for (auto item : solver.table.string_get(i)) {
            if (*item && !block_set.insert(*item).second) {
                throw std::runtime_error("Number intersection error!");
            }
        }
        block_set.clear();
        for (auto item : solver.table.column_get(i)) {
            if (*item && !block_set.insert(*item).second) {
                throw std::runtime_error("Number intersection error!");
            }
        }
        block_set.clear();
        for (auto item : solver.table.square_get(i)) {
            if (*item && !block_set.insert(*item).second) {
                throw std::runtime_error("Number intersection error!");
            }
        }
        block_set.clear();
    }

    for (int i = 0; i < 9; i++) {
        for (auto j : solver.table.column_get(i)) solver.column_sets[i].erase(*j);
        for (auto j : solver.table.string_get(i)) solver.string_sets[i].erase(*j);
        for (auto j : solver.table.square_get(i)) solver.square_sets[i].erase(*j);
    }

    table = solver.table;
    column_sets = solver.column_sets;
    string_sets = solver.string_sets;
    square_sets = solver.square_sets;
}

void Solver::print(std::ostream& stream) {
    stream << table;
}

void Solver::clear() {
    for (int i = 0; i < 9; i++) {
        column_sets[i] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
        string_sets[i] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
        square_sets[i] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
        for (int j = 0; j < 9; j++) table.get(i, j) = 0;
    }
}

bool Solver::solve() {
    std::set<int> open;
    for (int i = 0; i < 9; i++) if (square_sets[i].size()) open.insert(i);

    tsa allowed;
    int x, y, success = 0;

    for (auto i = open.begin(); i != open.end(); i) {
        x = (*i % 3) * 3;
        y = (*i / 3) * 3;
        square_allowed_create(allowed, x, y);

        if (square_solve_1(allowed, x, y)) {
            success = 1;
            if (square_sets[*i].empty()) {
                open.erase(i);
                i = open.begin();
            }
        }
        if (square_solve_2(allowed, x, y)) {
            success = 1;
            if (square_sets[*i].empty()) {
                open.erase(i);
                i = open.begin();
            }
        }

        if (success == 0) i++;

        allowed.clear();
        success = 0;
    }

    // ...

    for (int i = 0; i < 9; i++) if (square_sets[i].size()) return false;
    return true;
}

// PROTECTED

void Solver::square_allowed_create(tsa& allowed, const int& x, const int& y) {
    int dx, dy, index = y + x / 3;

    for (int i = 0; i < 9; i++) {
        dx = x + i % 3;
        dy = y + i / 3;
        if (!table.get(dy, dx)) {
            allowed[i] = {};
            for (auto &j : square_sets[index]) {
                if (string_sets[dy].count(j) && column_sets[dx].count(j)) {
                    allowed[i].insert(j);
                }
            }
        }
    }
}

bool Solver::square_solve_1(tsa& allowed, const int& x, const int& y) {
    short value = 0, index = x + y / 3;

    for (auto i = allowed.begin(); i != allowed.end();) {
        if (i->second.size() == 1) {
            value = *i->second.begin();

            table.get(y + i->first / 3, x + i->first % 3) = value;
            string_sets[y + i->first / 3].erase(value);
            column_sets[x + i->first % 3].erase(value);
            square_sets[index].erase(value);

            allowed.erase(i);
            for (auto &j : allowed) j.second.erase(value);
            i = allowed.begin();
        }
        else i++;
    }

    return value != 0;
}

bool Solver::square_solve_2(tsa& allowed, const int& x, const int& y) {
    short index = x + y / 3, result = 0;

    std::multiset<short> mset;
    for (auto &i : allowed) mset.insert(i.second.begin(), i.second.end());

    for (int i = 1; i < 10; i++) if (mset.count(i) == 1) {
        result = 1;
        for (auto &j : allowed) {
            if (j.second.count(i)) {
                table.get(y + j.first / 3, x + j.first % 3) = i;
                string_sets[y + j.first / 3].erase(i);
                column_sets[x + j.first % 3].erase(i);
                square_sets[index].erase(i);

                allowed.erase(j.first);
                break;
            }
        }
    }

    return result != 0;
}
