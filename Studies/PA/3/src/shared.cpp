#include "shared.hpp"
#include <iomanip>

matrix get_matrix(int size) {
    matrix m(size, vector(size, 1));
    for (int i = 0; i < size; i++) m[(i + 3) % size][i] = 0;
    return m;
}

vector get_vector(int size, int fill) {
    vector v(size);
    for (int i = 0; i < size; i++) v[i] = fill;
    return v;
}

vector get_vector(int size, int f, int t) {
    vector v(size);
    double step = double(t - f) / size;
    for (int i = 0; i < size; i++) v[i] = f + int(i * step);
    return v;
}

vector operator*(const matrix &m, const vector &v) {
    vector b(m.size(), 0);
    for (int i = 0; i < m.size(); i++) for (int j = 0; j < v.size(); j++) b[i] += m[i][j] * v[j];
    return b;
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
    return out;
}
