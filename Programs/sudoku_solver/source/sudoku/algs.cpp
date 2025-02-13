#include "source/sudoku/algs.hpp"

Solver::Solver() {
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            set_data.get(i, j) = {1, 2, 3, 4, 5, 6, 7, 8, 9};
        }
    }
}

void Solver::load(std::istream& stream) {
    Table<short> temp_data;
    stream >> temp_data;

    if (!check_data(temp_data)) throw std::runtime_error("Number intersection error!");

    Table<std::set<short>> temp_set_data;

    std::vector<std::set<short>> c_allowed(9), r_allowed(9), q_allowed(9);
    for (int i = 0; i < 9; i++) {
        q_allowed[i] = r_allowed[i] = c_allowed[i] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
        for (auto &j : temp_data.column_get(i)) c_allowed[i].erase(*j);
        for (auto &j : temp_data.string_get(i)) r_allowed[i].erase(*j);
        for (auto &j : temp_data.square_get(i)) q_allowed[i].erase(*j);
    }

    // Нужно в трех циклах от 0 до 9 сделать сначала заполнение строк строками. Потом все остальное ...

    // "Unsolvable problem error!"

    set_data = temp_set_data;
    data = temp_data;
}

void Solver::print(std::ostream& stream) {
    stream << data;
}

void Solver::clear() {
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            set_data.get(i, j) = {1, 2, 3, 4, 5, 6, 7, 8};
            data.set(i, j, 0);
        }
    }
}

bool Solver::solve() {
    int index = 0;
    while (index < 9) {
        if (last_hero_square(index)) index = 0;
        else index++;
    }

    // ...

    for (int i = 0; i < 9; i++) for (int j = 0; j < 9; j++) if (!data.get(i, j)) return false;
    return true;
}

// PROTECTED

bool Solver::check_data(Table<short>& t_data) {
    std::set<short> block_set;
    for (int i = 0; i < 9; i++) {
        for (auto& item : t_data.string_get(i)) {
            if (block_set.count(*item)) return false;
            else if (item) block_set.insert(*item);
        }
        block_set.clear();
        for (auto& item : t_data.column_get(i)) {
            if (block_set.count(*item)) return false;
            else if (item) block_set.insert(*item);
        }
        block_set.clear();
        for (auto& item : t_data.square_get(i)) {
            if (block_set.count(*item)) return false;
            else if (item) block_set.insert(*item);
        }
        block_set.clear();
    }
    return true;
}

bool Solver::last_hero_square(const int& index) {
    std::map<int, std::pair<int, int>> counts;
    for (int value = 1; value < 10; value++) counts[value] = {0, 0};

    auto sets_iter = set_data.square_get(index).begin();
    for (int i = 0; i < 9; i++) {
        for (auto &value : **(sets_iter + i)) {
            if (counts[value].first++ == 0) counts[value].second = i;
        }
    }

    bool result = false;
    for (auto &i : counts) {
        if (i.second.first == 1) {
            result = true;

            int x = (index % 3) * 3 + i.second.second % 3;
            int y = (index / 3) * 3 + i.second.second / 3;

            data.set(y, x, i.first);
            for (auto &a : set_data.column_get(x)) a->erase(i.first);
            for (auto &a : set_data.string_get(y)) a->erase(i.first);
        }
    }
    return result;
}
