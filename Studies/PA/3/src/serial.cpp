#include <iostream>
#include <iomanip>
#include <vector>
#include <omp.h>


// Generation functions

typedef std::vector<double> vector;
typedef std::vector<vector> matrix;

matrix Matrix(vector x) {
    matrix m(x.size(), vector(x.size() + 1, 0));
    int s = x.size();
    double b = 0;
    
    for (int i = 0; i < s; i++) {
        m[i][i] += 1;
        for (int j = 0; j < s; j++) b += (m[i][j] += i + j) * x[j];
        m[i][s] += b;
        b = 0;
    }
    
    return m;
}

std::ostream& operator<<(std::ostream& out, const matrix& m) {
    for (auto& i : m) {
        for (auto& j : i) out << std::setw(6) << j << "  ";
        out << "\n";
    }
    return out;
}

std::ostream& operator<<(std::ostream& out, const vector& v) {
    for (auto& i : v) out << std::setw(6) << i << "  ";
    return out << "\n";
}


// Algorithm functions

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

void do_slae_with_kramer(const matrix m, vector& result) {
    std::vector<int> xs(m.size());
    for (int i = 0; i < m.size(); i++) xs[i] = i;
    double det = determinant(m, 0, xs);
    
    for (int i = 0; i < m.size(); i++) {
        xs[i] = m.size();
        result[i] = determinant(m, 0, xs) / det;
        xs[i] = i;
    }
}


// Main

int main() {
    vector ex{0, 1, 2, 3}, x(4);
    matrix m = Matrix(ex);
    
    std::cout << m << ex;
    do_slae_with_kramer(m, x);
    std::cout << '\n' << m << x;
    
    return 0;
}

