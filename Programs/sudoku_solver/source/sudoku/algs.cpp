#include "source/sudoku/algs.hpp"

Solver::Solver() {
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            set_data.get(i, j) = {1, 2, 3, 4, 5, 6, 7, 8};
        }
    }
}

void Solver::load(std::istream& stream) {
    Table<short> temp_data;
    stream >> temp_data;

    std::set<short> block_set;
    for (int i = 0; i < 9; i++) {
        for (auto& item : temp_data.rget(i)) {
            if (block_set.count(item)) throw std::runtime_error("Number intersection error!");
            else if (item) block_set.insert(item);
        }
        block_set.clear();
        for (auto& item : temp_data.cget(i)) {
            if (block_set.count(item)) throw std::runtime_error("Number intersection error!");
            else if (item) block_set.insert(item);
        }
        block_set.clear();
        for (auto& item : temp_data.qget(i)) {
            if (block_set.count(item)) throw std::runtime_error("Number intersection error!");
            else if (item) block_set.insert(item);
        }
        block_set.clear();
    }

    // SetTable temp_set_data;
    // std::set<short> not_allowed;
    // for (int i = 0; i < 9; i++) {
    //     for (int j = 0; j < 9; j++) {
    //         if (!data.get(i, j)) {
    //             for (auto& e : data.rget(i)) not_allowed.insert(e);
    //             for (auto& e : data.cget(j)) not_allowed.insert(e);
    //             for (auto& e : data.qget(i, j)) not_allowed.insert(e);
    //             if (not_allowed.size() == 10) return false;

    //             for (int k = 1; k < 10; k++) if (!not_allowed.count(k)) set_data.get(i, j).insert(k);
    //             not_allowed.clear();
    //         }
    //     }
    // }
    // 
    // "Unsolvable problem error!"

    data = temp_data;
}

void Solver::print(std::ostream& stream) {
    stream << data;
}

void Solver::clear() {
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            set_data.get(i, j) = {1, 2, 3, 4, 5, 6, 7, 8};
            data.get(i, j) = 0;
        }
    }
}

bool Solver::solve() {
    int index = 0;
    while (index < 9) {
        point p = last_hero_square(index);
        if (p.v != 0) {
            data.get(p.y, p.x) = p.v;
            for (auto &i : set_data.cget(p.x)) i.get().erase(p.v);
            for (auto &i : set_data.rget(p.y)) i.get().erase(p.v);
            for (auto &i : set_data.qget(p.y - p.y % 3 + p.x % 3)) i.get().erase(p.v);
            index = 0;
        }
        else index++;
    }

    // ...

    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            if (data.get(i, j) == 0) return false;
        }
    }
    return true;
}

// PROTECTED

point Solver::last_hero_square(int index) {
    point result = {0, 0, 0};
    int count = 0;
    for (int v = 1; v < 10; v++) {
        for (int i = index - index % 3; i < index - index % 3 + 3; i++) {
            for (int j = (index % 3) * 3; j < (index % 3) * 3 + 3; j++) {
                if (set_data.get(i, j).count(v)) {
                    result = {i, j, v};
                    count++;
                }
                if (count > 1) break;
            }
            if (count > 1) break;
        }
        if (count == 0) throw std::runtime_error("Unsolvable task at square " + std::to_string(index) + "!");
        if (count == 1) return result;
        count = 0;
        result = {0, 0, 0};
    }
    return result;
}
