#include "source/sudoku/table.hpp"

Table::Table() {
    data.assign(9, std::vector<short>(9));
}

short Table::get(const int& y, const int& x) const {
    if (x < 0 || x > 8 || y < 0 || y > 8) throw std::out_of_range("Out of bounds!");
    return data[y][x];
}

short& Table::rget(const int& y, const int& x) {
    if (x < 0 || x > 8 || y < 0 || y > 8) throw std::out_of_range("Out of bounds!");
    return data[y][x];
}

std::vector<short*> Table::column_get(const int& x) {
    if (x < 0 || x > 8) throw std::out_of_range("Out of bounds!");
    std::vector<short*> result;
    for (int y = 0; y < 9; y++) result.push_back(&data[y][x]);
    return result;
}

std::vector<short*> Table::string_get(const int& y) {
    if (y < 0 || y > 8) throw std::out_of_range("Out of bounds!");
    std::vector<short*> result;
    for (int x = 0; x < 9; x++) result.push_back(&data[y][x]);
    return result;
}

std::vector<short*> Table::square_get(const int& q) {
    if (q < 0 || q > 8) throw std::out_of_range("Out of bounds!");
    int x = (q % 3) * 3, y = q - q % 3;
    std::vector<short*> result;
    for (int i = y; i < y + 3; i++) for (int j = x; j < x + 3; j++) result.push_back(&data[i][j]);
    return result;
}

std::istream& operator>>(std::istream& stream, Table& data) {
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            if (stream.eof()) throw std::invalid_argument("Not enough data to initialize table!");
            stream >> data.data[i][j];
        }
    }
    return stream;
}

std::ostream& operator<<(std::ostream& stream, const Table& data) {
    for (int i = 0; i < 9; i++) {
        stream << data.data[i][0];
        for (int j = 1; j < 9; j++) stream << (j % 3 == 0 ? '\t' : ' ') << data.data[i][j];
        stream << (i % 3 == 2 ? "\n\n" : "\n");
    }
    return stream;
}
