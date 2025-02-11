#include <filesystem>
#include <fstream>

#include "source/sudoku/algs.hpp"

namespace fs = std::filesystem;

int main(int argc, char* argv[]) {
    Solver sudoku;

    for (auto& entry : fs::directory_iterator(fs::path("./data").lexically_normal())) {
        std::ifstream file(entry.path());
        if (!file.is_open()) continue;

        std::cout << "@ Test " << entry.path().filename() << "\n\n";
        try {
            sudoku.load(file);
            if (sudoku.solve()) std::cout << "Success!\n\n";
            else std::cout << "Not success!\n\n";
            sudoku.print(std::cout);
        }
        catch (std::runtime_error error) {
            std::cout << error.what() << "\n\n";
        }
        sudoku.clear();

        file.close();
    }

    return 0;
}
