#include <vector>
#include <set>


class Sudoku {
public:
    typedef std::vector<int> row;
    typedef std::vector<row> map;
    typedef std::vector<std::set<int>> setmap;

    Sudoku();

    bool load(const map& data);
    map data();

    bool solve();
    bool solve(map& table);

private:
    map ddata;
    setmap needed_q;
    setmap needed_r;
    setmap needed_c;
};
