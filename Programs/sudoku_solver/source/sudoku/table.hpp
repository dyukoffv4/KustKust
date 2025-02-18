#pragma once

#include <iostream>
#include <vector>

class Table;

std::istream& operator>>(std::istream& stream, Table& data);
std::ostream& operator<<(std::ostream& stream, const Table& data);

class Table {
public:
    Table();

    short get(const int& y, const int& x) const;
    short& rget(const int& y, const int& x);
    
    std::vector<short*> column_get(const int& x);
    std::vector<short*> string_get(const int& y);
    std::vector<short*> square_get(const int& q);
    
protected:
    std::vector<std::vector<short>> data;

    friend std::istream& operator>>(std::istream&, Table&);
    friend std::ostream& operator<<(std::ostream&, const Table&);
};
