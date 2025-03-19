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
            sudoku.enter(file);
            std::cout << "Entered:\n\n";
            sudoku.print(std::cout);
            if (sudoku.solve()) std::cout << "Success!\n\n";
            else std::cout << "Not success!\n\n";
            sudoku.print(std::cout);
            sudoku.clear();
        }
        catch (std::runtime_error error) {
            std::cout << error.what() << "\n\n";
        }
        catch (std::logic_error error) {
            std::cout << error.what() << "\n\n";
        }

        file.close();
    }

    return 0;
}
