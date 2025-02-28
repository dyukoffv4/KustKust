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

short Solver::get(const int& x, const int& y) const {
    return table.get(x, y);
}

bool Solver::set(const int& x, const int& y, const short& v) {
    if (v < 0 || v > 9) throw std::invalid_argument("Wrong sudoku value!");

    short& old_v = table.rget(x, y), q = y - y % 3 + x / 3;

    if (v != 0) {
        if (!column_sets[x].count(v)) return false;
        if (!string_sets[y].count(v)) return false;
        if (!square_sets[q].count(v)) return false;
        column_sets[x].erase(v);
        string_sets[y].erase(v);
        square_sets[q].erase(v);
    }
    if (old_v != 0) {
        column_sets[x].insert(old_v);
        string_sets[y].insert(old_v);
        square_sets[q].insert(old_v);
    }
    old_v = v;

    return true;
}

void Solver::clear() {
    for (int i = 0; i < 9; i++) {
        column_sets[i] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
        string_sets[i] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
        square_sets[i] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
        for (int j = 0; j < 9; j++) table.rget(i, j) = 0;
    }
}

bool Solver::solve() {
    tsa allowed;
    int x, y;
    bool success = false;

    for (int i = 0; i < 9; i++) {
        if (square_sets[i].empty()) continue;

        x = (i % 3) * 3;
        y = (i / 3) * 3;
        square_allowed_create(allowed, x, y);

        success = false;
        if (square_solve_1(allowed, x, y)) success = true;
        if (square_solve_2(allowed, x, y)) success = true;
        if (success) i = -1;

        allowed.clear();
    }

    // ...

    for (int i = 0; i < 9; i++) if (square_sets[i].size()) return false;
    return true;
}

// PROTECTED

void Solver::square_allowed_create(tsa& allowed, const int& x, const int& y) {
    int xi, yi, qi = y + x / 3;

    for (int i = 0; i < 9; i++) {
        xi = x + i % 3;
        yi = y + i / 3;

        if (table.rget(yi, xi) == 0) {
            allowed[i] = {};
            for (auto &j : square_sets[qi]) {
                if (string_sets[yi].count(j) && column_sets[xi].count(j)) allowed[i].insert(j);
            }
        }
    }
}

bool Solver::square_solve_1(tsa& allowed, const int& x, const int& y) {
    short value = 0;
    int xi, yi, qi = y + x / 3;

    auto i = allowed.begin();
    while (i != allowed.end()) {
        if (i->second.size() == 1) {
            xi = x + i->first % 3;
            yi = y + i->first / 3;

            table.rget(yi, xi) = value = *(i->second.begin());
            string_sets[yi].erase(value);
            column_sets[xi].erase(value);
            square_sets[qi].erase(value);

            allowed.erase(i);
            for (auto &j : allowed) j.second.erase(value);

            i = allowed.begin();
        }
        else i++;
    }

    return value;
}

bool Solver::square_solve_2(tsa& allowed, const int& x, const int& y) {
    bool result = false;
    int xi, yi, qi = y + x / 3;

    std::map<short, std::pair<int, int>> counts;
    for (short i = 1; i < 10; i++) counts[i] = {0, 0};
    for (auto& i : allowed) for (auto& j : i.second) {
        counts[j].first++;
        counts[j].second = i.first;
    }

    for (int i = 1; i < 10; i++) {
        if (counts[i].first == 1) {
            result = true;
            xi = x + counts[i].second % 3;
            yi = y + counts[i].second / 3;

            table.rget(yi, xi) = i;
            string_sets[yi].erase(i);
            column_sets[xi].erase(i);
            square_sets[qi].erase(i);

            allowed.erase(counts[i].second);
        }
    }

    return result;
}
