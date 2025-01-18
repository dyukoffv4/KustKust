#include "test.hpp"
#include <iostream>


Sudoku::Sudoku(const map& data) : data(data) {
    rule1 = rule2 = rule3 = pmap(9);
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            rule1[i].push_back(&(this->data[i][j]));
            rule2[i].push_back(&(this->data[j][i]));
            rule3[i / 3 * 3 + j / 3].push_back(&(this->data[i][j]));
        }
    }
}

bool Sudoku::check_health() {
    std::set<int> container;
    for (auto &c : std::vector<pmap>{rule1, rule2, rule3}) {
        for (auto &i : c) {
            for (auto &j : i) {
                if (*j != 0) {
                    if (container.count(*j)) return false;
                    container.insert(*j);
                }
            }
            container.clear();
        }
    }
    return true;
}

bool Sudoku::solve() {
    // Not done yet
    return true;
}

bool Sudoku::solve(map& table) {
    // Not done yet
    return true;
}

Sudoku::map Sudoku::get_data() {
    return data;
}

/*
int main(int argc, char* argv[]) {
    std::cout << "Enter sudoku template. Print zero in empty places.\n\n";

    Sudoku::map table(9, Sudoku::row(9));
    for (auto& i : table) for (auto& j : i) { std::cin >> j; if (j < 0 || j > 9) return 1; }

    Sudoku sudoku(table);
    if (!sudoku.check_health()) return 2;
    
    std::cout << "\nStart calculating.\n\n";

    return 0;
}
*/
