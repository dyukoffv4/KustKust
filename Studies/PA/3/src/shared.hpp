#include <iostream>
#include <vector>

typedef std::vector<int> vector;
typedef std::vector<vector> matrix;

matrix get_matrix(int);

vector get_vector(int);

vector get_vector(int, int);

vector operator*(const matrix &, const vector &);

std::ostream &operator<<(std::ostream &, const matrix &);

std::ostream &operator<<(std::ostream &, const vector &);
