#include "shared.hpp"
#include <omp.h>


void swap(matrix &m, int s1, int s2) {
    vector temp = m[s1];
    m[s1] = m[s2];
    m[s1] = temp;
}

double determinant(const matrix &m) {
    int m_size = m.size(), e_size = m.size() + 1;

    matrix nm(e_size, vector(e_size, 1));
    for (int i = 0; i < m_size; i++) for (int j = 0; j < m_size; j++) nm[i + 1][j + 1] = m[i][j];

    for (int k = 1; k < e_size - 1; k++) {
        if (!nm[k - 1][k - 1]) {
            for (int i = k; i < e_size; i++) {
                if (nm[i][k - 1]) {
                    swap(nm, i, k - 1);
                    break;
                }
            }
            if (!nm[k - 1][k - 1]) return 0;
        }

        for (int i = k + 1; i < e_size; i++) {
            for (int j = k + 1; j < e_size; j++) {
                nm[i][j] = (nm[i][j] * nm[k][k] - nm[i][k] * nm[k][j]) / nm[k - 1][k - 1];
            }
        }
    }

    return nm[m_size][m_size];
}

void kramerSLAE(const matrix &m, vector &result) {
    matrix m2(m.size(), vector(m.size()));
    for (int i = 0; i < m.size(); i++) for (int j = 0; j < m.size(); j++) m2[i][j] = m[i][j];

    vector b(m.size());
    for (int i = 0; i < m.size(); i++) b[i] = m[m.size()][i];

    double det = determinant(m2);

    matrix m2_t = m2;
    for (int i = 0; i < m.size(); i++) {
        for (int j = 0; j < m.size(); j++) m2_t[i][j] = b[j];
        result[i] = determinant(m2_t) / det;
        for (int j = 0; j < m.size(); j++) m2_t[i][j] = m2[i][j];
    }
}


int main() {
    vector ex, x;
    matrix m;

    for (int i = 5; i < 11; i++) {
        ex = x = vector(i);
        for (int j = 0; j < i; j++) ex[j] = j;
        m = matrixSLAE(ex);

        std::cout << "\nsize: " << i << '\n' << m << '\n' << ex;
        double t_start = omp_get_wtime();
        kramerSLAE(m, x);
        std::cout << "\ntime: " << (omp_get_wtime() - t_start) * 1000 << '\n' << x << '\n';
    }

    return 0;
}
