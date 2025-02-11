#include "source/sudoku/algs.hpp"

bool check_sudoku(ShortTable& data) {
    ShortTable new_data;
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            short tile = data.get(i, j);
            if (tile) {
                for (auto& e : new_data.rget(i)) if (e == tile) return false;
                for (auto& e : new_data.cget(j)) if (e == tile) return false;
                for (auto& e : new_data.qget(i, j)) if (e == tile) return false;
                new_data.get(i, j) = tile;
            }
        }
    }
    return true;
}

bool init_sudoku_set(SetTable& set_data, ShortTable& data) {
    std::set<short> not_allowed;
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            if (!data.get(i, j)) {
                for (auto& e : data.rget(i)) not_allowed.insert(e);
                for (auto& e : data.cget(j)) not_allowed.insert(e);
                for (auto& e : data.qget(i, j)) not_allowed.insert(e);
                if (not_allowed.size() == 10) return false;

                for (int k = 1; k < 10; k++) if (!not_allowed.count(k)) set_data.get(i, j).insert(k);
                not_allowed.clear();
            }
        }
    }
    return true;
}

point last_hero_square(SetTable& set_data, int qrow, int qcol) {
    point result = {0, 0, 0};
    int count = 0;
    for (int v = 1; v < 10; v++) {
        for (int i = qrow * 3; i < qrow * 3 + 3; i++) {
            for (int j = qcol * 3; j < qcol * 3 + 3; j++) {
                if (set_data.get(i, j).count(v)) {
                    result = {i, j, v};
                    count++;
                }
                if (count > 1) break;
            }
            if (count > 1) break;
        }
        if (count == 0) throw std::runtime_error("Unsolvable task at square " + std::to_string(qcol * 3 + qrow) + "!");
        if (count == 1) return result;
        count = 0;
        result = {0, 0, 0};
    }
    return result;
}
 
bool solve_sudoku(ShortTable& data, SetTable& set_data) {
    int index = 0;
    while (index < 9) {
        point p = last_hero_square(set_data, index / 3, index % 3);
        if (p.v != 0) {
            data.get(p.y, p.x) = p.v;
            for (auto &i : set_data.cget(p.x)) i.get().erase(p.v);
            for (auto &i : set_data.rget(p.y)) i.get().erase(p.v);
            for (auto &i : set_data.qget(p.y, p.x)) i.get().erase(p.v);
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
