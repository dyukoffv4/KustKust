#include <filesystem>

#include <strstream>
#include <iostream>
#include <fstream>

#include <vector>
#include <set>

using std::istream, std::ostream, std::cout, std::cin, std::ifstream, std::ofstream;
namespace fs = std::filesystem;

/// @class Table
/// Start of defenition
/// <--/-->

template<class T>
using refvector = std::vector<std::reference_wrapper<T>>;

template<class T>
class Table;

template<class T>
istream& operator>>(istream& in, Table<T>& data);

template<class T>
ostream& operator<<(ostream& out, const Table<T>& data);

template<class T>
class Table {
public:
    Table() {
        data.assign(9, std::vector<T>(9));
    }

    T& get(const int& y, const int& x) {
        if (x < 0 || x > 8 || y < 0 || y > 8) throw std::out_of_range("Out of bounds!");
        return data[y][x];
    }

protected:
    std::vector<std::vector<T>> data;

    template<class U>
    friend istream& operator>>(istream&, Table<U>&);

    template<class U>
    friend ostream& operator<<(ostream&, const Table<U>&);
};

template<class T>
istream& operator>>(istream& in, Table<T>& data) {
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            if (in.eof()) throw "Not enough data to initialize table!";
            in >> data.data[i][j];
        }
    }
    return in;
}

template<class T>
ostream& operator<<(ostream& out, const Table<T>& data) {
    for (int i = 0; i < 9; i++) {
        out << data.data[i][0];
        for (int j = 1; j < 9; j++) out << (j % 3 == 0 ? '\t' : ' ') << data.data[i][j];
        out << (i % 3 == 2 ? "\n\n" : "\n");
    }
    return out;
}

/// @class SudokuTable
/// @class SetSudokuTable
/// Start of defenition
/// <--/-->

class SudokuTable : public Table<short> {
public:
    refvector<short> cget(const int& x) {
        if (x < 0 || x > 8) throw std::out_of_range("Out of bounds!");
        refvector<short> result;
        for (int y = 0; y < 9; y++) result.push_back(data[y][x]);
        return result;
    }

    refvector<short> rget(const int& y) {
        if (y < 0 || y > 8) throw std::out_of_range("Out of bounds!");
        refvector<short> result;
        for (int x = 0; x < 9; x++) result.push_back(data[y][x]);
        return result;
    }

    refvector<short> qget(const int& y, const int& x) {
        if (x < 0 || x > 8 || y < 0 || y > 8) throw std::out_of_range("Out of bounds!");
        refvector<short> result;
        for (int i = y - y % 3; i < y - y % 3 + 3; i++) {
            for (int j = x - x % 3; j < x - x % 3 + 3; j++) {
                result.push_back(data[i][j]);
            }
        }
        return result;
    }
};

class SetSudokuTable : public Table<std::set<short>> {
public:
    void clear() {
        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 9; j++) {
                data[i][j].clear();
            }
        }
    }
};

/// @def check_sudoku
/// @def init_sudoku_set
/// @def solve_sudoku
/// Start fo defenition
/// <--/-->

bool check_sudoku(SudokuTable& data) {
    SudokuTable new_data;
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

bool init_sudoku_set(SetSudokuTable& set_data, SudokuTable& data) {
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

bool solve_sudoku(SudokuTable& data, SetSudokuTable& set_data) {
    SetSudokuTable value_row_col;

    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            auto tile_set = set_data.get(i, j);
            for (int k = 1; k < 10; k++) {
                if (tile_set.count(k)) {
                    value_row_col.get(k - 1, i).insert(j);
                }
            }
        }
    }

    // Algorithms for sudoku solve. Solve for squares, methods by queue. Annalyze, and optimize process from queue to targeting.

    return true;
}

/// @def main
/// Entry point of program
/// <--/-->

int main(int argc, char* argv[]) {
    SudokuTable sudoku;
    SetSudokuTable sudoku_set;

    for (auto& entry : fs::directory_iterator(fs::path("./data").lexically_normal())) {
        ifstream file(entry.path());
        if (!file.is_open()) continue;
        file >> sudoku;
        file.close();

        cout << "@ Test " << entry.path().filename() << "\n\n";

        if (!check_sudoku(sudoku)) {
            cout << "Number intersection error!\n\n";
            continue;
        }

        if (!init_sudoku_set(sudoku_set, sudoku)) {
            sudoku_set.clear();
            cout << "Unsolvable problem error!\n\n";
            continue;
        }

        if (solve_sudoku(sudoku, sudoku_set)) cout << "Success!\n\n";
        else cout << "Not success!\n\n";
        cout << sudoku;

        sudoku_set.clear();
    }

    return 0;
}
