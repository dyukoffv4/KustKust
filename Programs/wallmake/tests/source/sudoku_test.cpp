#include "source/utilities/sudoku.hpp"
#include <iostream>


Sudoku::map get_test(int number) {
    Sudoku::map table;
    switch (number)
    {
    case 0:
        table.push_back({1, 0, 0, 2, 0, 0, 3, 0, 0});
        table.push_back({0, 0, 0, 0, 0, 0, 0, 0, 0});
        table.push_back({0, 0, 0, 0, 0, 0, 0, 0, 0});
        table.push_back({0, 1, 0, 0, 2, 0, 0, 3, 0});
        table.push_back({0, 0, 0, 0, 0, 0, 0, 0, 0});
        table.push_back({0, 0, 0, 0, 0, 0, 0, 0, 0});
        table.push_back({0, 0, 1, 0, 0, 2, 0, 0, 3});
        table.push_back({0, 0, 0, 0, 0, 0, 0, 0, 0});
        table.push_back({0, 0, 0, 0, 0, 0, 0, 0, 0});
        break;
    
    default:
        throw std::invalid_argument("Test " + std::to_string(number) + " doesn't exist!");
    }
    return table;
}


int main(int argc, char* argv[]) {
    Sudoku sudoku;
    bool success;
    for (int i = 0; i < 1; i++) {
        if (!sudoku.setdata(get_test(i))) {
            std::cout << "Test number " << i << ". Invalid sudoku map!\n";
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
