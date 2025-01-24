#include <filesystem>
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;
namespace fs = std::filesystem;

/// @class Table
/// Start of defenition
/// <--/-->

class Table;

istream& operator>>(istream& in, Table& data);
ostream& operator<<(ostream& out, const Table& data);

class Table {
public:
    Table() {
        data.assign(9, vector<short>(9));
    }

    short* get(const int& y, const int& x) {
        return &data[y][x];
    }

    std::vector<short*> cget(const int& x) {
        std::vector<short*> result;
        for (int y = 0; y < 9; y++) result.push_back(&data[y][x]);
        return result;
    }

    std::vector<short*> rget(const int& y) {
        std::vector<short*> result;
        for (int x = 0; x < 9; x++) result.push_back(&data[y][x]);
        return result;
    }

private:
    vector<vector<short>> data;

    friend istream& operator>>(istream&, Table&);
    friend ostream& operator<<(ostream&, const Table&);
};

istream& operator>>(istream& in, Table& data) {
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            if (in.eof()) throw "Not enough data to initialize table!";
            in >> data.data[i][j];
        }
    }
    return in;
}

ostream& operator<<(ostream& out, const Table& data) {
    for (int i = 0; i < 9; i++) {
        out << data.data[i][0];
        for (int j = 1; j < 9; j++) out << (j % 3 == 0 ? '\t' : ' ') << data.data[i][j];
        out << (i % 3 == 2 ? "\n\n" : "\n");
    }
    return out;
}

/// @def check_sudoku
/// @def solve_sudoku
/// Start fo defenition
/// <--/-->

bool check_sudoku(const Table& data) {
    return true;
}

bool solve_sudoku(const Table& data) {
    return true;
}

/// @def main
/// Entry point of program
/// <--/-->

int main(int argc, char* argv[]) {
    Table sudoku;

    for (auto& entry : fs::directory_iterator(fs::path("./source/tests").lexically_normal())) {
        ifstream file(entry.path());
        if (!file.is_open()) continue;
        file >> sudoku;

        cout << "@ Test " << entry.path().filename() << "\n\n";

        if (!check_sudoku(sudoku)) {
            cout << "Invalid sudoku format!";
            continue;
        }

        if (solve_sudoku(sudoku)) cout << "Success!\n\n";
        else cout << "Not success!\n\n";
        cout << sudoku;
    }

    return 0;
}
