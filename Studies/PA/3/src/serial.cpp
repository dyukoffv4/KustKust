#include "shared.hpp"
#include <omp.h>


double determinant(const matrix m, int y, std::vector<int> xs) {
    if (xs.size() == 2) return m[y][xs[0]] * m[y + 1][xs[1]] - m[y][xs[1]] * m[y + 1][xs[0]];
    double result = 0.0;
    std::vector<int> nxs;

    for (int i = 0; i < xs.size(); i += 2) {
        nxs = xs;
        nxs.erase(nxs.begin() + i);
        result += m[y][xs[i]] * determinant(m, y + 1, nxs);
    }

    for (int i = 1; i < xs.size(); i += 2) {
        nxs = xs;
        nxs.erase(nxs.begin() + i);
        result -= m[y][xs[i]] * determinant(m, y + 1, nxs);
    }

    return result;
}

void kramerSLAE(const matrix &m, vector &result) {
    std::vector<int> xs(m.size());
    for (int i = 0; i < m.size(); i++) xs[i] = i;
    double det = determinant(m, 0, xs);

    for (int i = 0; i < m.size(); i++) {
        xs[i] = m.size();
        result[i] = determinant(m, 0, xs) / det;
        xs[i] = i;
    }
}


int main() {
    vector ex{0, 1, 2, 3}, x(4);
    matrix m = matrixSLAE(ex);

    std::cout << m << ex;
    kramerSLAE(m, x);
    std::cout << '\n' << m << x;

    return 0;
}
