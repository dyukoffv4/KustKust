#include <stdexcept>
#include <vector>
#include <set>


class Sudoku {
public:
    typedef std::vector<int> row;
    typedef std::vector<row> map;
    typedef std::vector<std::set<int>> setmap;

    Sudoku();

    bool setdata(const map& data);
    map getdata();

    bool set(const int& row, const int& col, const int& val);
    int get(const int& row, const int& col);

    bool solve();
    bool solve(map& table);

    void clear();

private:
    map ddata;
    setmap needed_q;
    setmap needed_r;
    setmap needed_c;
};
