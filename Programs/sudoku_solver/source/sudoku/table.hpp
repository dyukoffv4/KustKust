#pragma once

#include <iostream>
#include <vector>

template<class T>
class Table;

template<class T>
std::istream& operator>>(std::istream& in, Table<T>& data);

template<class T>
std::ostream& operator<<(std::ostream& out, const Table<T>& data);

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
    friend std::istream& operator>>(std::istream&, Table<U>&);

    template<class U>
    friend std::ostream& operator<<(std::ostream&, const Table<U>&);
};

template<class T>
std::istream& operator>>(std::istream& in, Table<T>& data) {
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            if (in.eof()) throw "Not enough data to initialize table!";
            in >> data.data[i][j];
        }
    }
    return in;
}

template<class T>
std::ostream& operator<<(std::ostream& out, const Table<T>& data) {
    for (int i = 0; i < 9; i++) {
        out << data.data[i][0];
        for (int j = 1; j < 9; j++) out << (j % 3 == 0 ? '\t' : ' ') << data.data[i][j];
        out << (i % 3 == 2 ? "\n\n" : "\n");
    }
    return out;
}
