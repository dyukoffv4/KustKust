#include <filesystem>
#include <iostream>
#include <fstream>
#include <vector>

using std::istream, std::ostream, std::cout, std::cin, std::ifstream, std::ofstream;
namespace fs = std::filesystem;

/// @class Table
/// Start of defenition
/// <--/-->

class Table;

istream& operator>>(istream& in, Table& data);
ostream& operator<<(ostream& out, const Table& data);

typedef std::vector<short*> pvector;

class Table {
public:
    Table() {
        data.assign(9, std::vector<short>(9));
    }

    short* get(const int& y, const int& x) {
        if (x < 0 || x > 8 || y < 0 || y > 8) throw std::out_of_range("Out of bounds!");
        return &data[y][x];
    }

    pvector cget(const int& x) {
        if (x < 0 || x > 8) throw std::out_of_range("Out of bounds!");
        pvector result;
        for (int y = 0; y < 9; y++) result.push_back(&data[y][x]);
        return result;
    }

    pvector rget(const int& y) {
        if (y < 0 || y > 8) throw std::out_of_range("Out of bounds!");
        pvector result;
        for (int x = 0; x < 9; x++) result.push_back(&data[y][x]);
        return result;
    }

    pvector qget(const int& y, const int& x) {
        if (x < 0 || x > 8 || y < 0 || y > 8) throw std::out_of_range("Out of bounds!");
        pvector result;
        for (int i = y - y % 3; i < y - y % 3 + 3; i++) {
            for (int j = x - x % 3; j < x - x % 3 + 3; j++) {
                result.push_back(&data[i][j]);
            }
        }
        return result;
    }

private:
    std::vector<std::vector<short>> data;

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

bool check_sudoku(Table& data) {
    Table new_data;
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            short tile = *data.get(i, j);
            if (tile) {
                for (auto& e : new_data.rget(i)) if (*e == tile) return false;
                for (auto& e : new_data.cget(j)) if (*e == tile) return false;
                for (auto& e : new_data.qget(i, j)) if (*e == tile) return false;
                *new_data.get(i, j) = tile;
            }
        }
    }
    return true;
}

bool solve_sudoku(Table& data) {
    std::vector<std::vector<std::vector<int>>> value_row_col(9);
    for (int i = 0; i < 9; i++) value_row_col[i] = std::vector<std::vector<int>>(9);

    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            short tile = *data.get(i, j);
            if (!tile) {
                bool not_inserted = true;
                for (int k = 1; k < 10; k++) {
                    bool forbidden = false;
                    for (auto &l : data.rget(i)) if (k == *l) forbidden = true;
                    if (forbidden) continue;
                    for (auto &l : data.cget(j)) if (k == *l) forbidden = true;
                    if (forbidden) continue;
                    for (auto &l : data.qget(i, j)) if (k == *l) forbidden = true;
                    if (forbidden) continue;
                    not_inserted = false;
                    value_row_col[k - 1][i].push_back(j);
                }
                if (not_inserted) return false;
            }
        }
    }

    // ---

    

    return true;
}

/// @def main
/// Entry point of program
/// <--/-->

int main(int argc, char* argv[]) {
    Table sudoku;

    for (auto& entry : fs::directory_iterator(fs::path("./data").lexically_normal())) {
        ifstream file(entry.path());
        if (!file.is_open()) continue;
        file >> sudoku;
        file.close();

        cout << "@ Test " << entry.path().filename() << "\n\n";

        if (!check_sudoku(sudoku)) {
            cout << "Invalid sudoku format!\n\n";
            continue;
        }

        if (solve_sudoku(sudoku)) cout << "Success!\n\n";
        else cout << "Not success!\n\n";
        cout << sudoku;
    }

    return 0;
}
