#include <iostream>
#include <iomanip>
#include <vector>

typedef std::vector<double> vector;
typedef std::vector<vector> matrix;

// Create matrix of System of Linear Equlites from Xs
// Input:   vector(N)
// Output:  matrix(N, N+1)
matrix matrixSLAE(vector);

std::ostream &operator<<(std::ostream &, const matrix &);

std::ostream &operator<<(std::ostream &, const vector &);
