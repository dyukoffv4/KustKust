#include <filesystem>
#include <fstream>

#include "source/sudoku/algs.hpp"

namespace fs = std::filesystem;

int main(int argc, char* argv[]) {
    SudokuTable sudoku;
    SetSudokuTable sudoku_set;

    for (auto& entry : fs::directory_iterator(fs::path("./data").lexically_normal())) {
        std::ifstream file(entry.path());
        if (!file.is_open()) continue;
        file >> sudoku;
        file.close();

        std::cout << "@ Test " << entry.path().filename() << "\n\n";

        if (!check_sudoku(sudoku)) {
            std::cout << "Number intersection error!\n\n";
            continue;
        }

        if (!init_sudoku_set(sudoku_set, sudoku)) {
            sudoku_set.clear();
            std::cout << "Unsolvable problem error!\n\n";
            continue;
        }

        if (solve_sudoku(sudoku, sudoku_set)) std::cout << "Success!\n\n";
        else std::cout << "Not success!\n\n";
        std::cout << sudoku;

        sudoku_set.clear();
    }

    return 0;
}
