#include "source/utilities/sudoku.hpp"
#include <iostream>
#include <list>


Sudoku::map get_test(int number) {
    Sudoku::row queue, line;
    Sudoku::map table;

    switch (number)
    {
    case 0:
        queue = {0, 3, 6, 1, 4, 7, 2, 5, 8};
        break;
    case 1:
        queue = {0, 1, 2, 3, 4, 5, 6, 7, 8};
        break;
    case 2:
        queue = {0, 6, 3, 2, 5, 8, 1, 7, 4};
        break;
    default:
        throw std::invalid_argument("Test " + std::to_string(number) + " doesn't exist!");
    }

    for (auto& i : queue) {
        for (int j = i; j < i + 9; j++) line.push_back(j % 9 + 1);
        table.push_back(line);
        line.clear();
    }
    for (int i = 0; i < 9; i++) table[i / 3][i % 3] = 0;

    return table;
}


int main(int argc, char* argv[]) {
    Sudoku sudoku;
    bool success;
    for (int i = 0; i < 3; i++) {
        if (!sudoku.setdata(get_test(i))) {
            std::cout << "Test number " << i << ". Invalid sudoku map!\n\n";
            continue;
        }
        
        success = sudoku.solve();
        std::cout << "Test number " << i << (success ? ". S" : ". Not s") << "uccess!\nTable:\n";
        for (auto& i : sudoku.getdata()) {
            for (auto& j : i) std::cout << j << ' ';
            std::cout << '\n';
        }
        std::cout << '\n';
    }
    return 0;
}
