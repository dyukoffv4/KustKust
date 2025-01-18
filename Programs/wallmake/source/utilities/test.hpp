#include <vector>
#include <set>


class Sudoku {
public:
    typedef std::vector<int> row;
    typedef std::vector<row> map;

    typedef std::vector<int*> prow;
    typedef std::vector<prow> pmap;

    Sudoku(const map& data);

    bool check_health();

    bool solve();
    bool solve(map& table);

    map get_data();

private:
    map data;
    pmap rule1;
    pmap rule2;
    pmap rule3;
};
