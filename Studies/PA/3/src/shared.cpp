#include "shared.hpp"
#include <iomanip>

matrix matrixSLAE(vector x) {
    matrix m(x.size(), vector(x.size() + 1, 0));
    int s = x.size();
    long b = 0;

    for (int i = 0; i < s; i++) {
        m[i][i] += 1;
        for (int j = 0; j < s; j++) b += (m[i][j] += i + j) * x[j];
        m[i][s] += b;
        b = 0;
    }

    return m;
}

std::ostream &operator<<(std::ostream &out, const matrix &m) {
    for (auto &i : m) {
        for (auto &j : i) out << std::setw(5) << j << "  ";
        out << "\n";
    }
    return out;
}

std::ostream &operator<<(std::ostream &out, const vector &v) {
    for (auto &i : v) out << std::setw(5) << i << "  ";
    return out << "\n";
}
