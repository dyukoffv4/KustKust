#include "parallel.hpp"

int parallel::determinant(const matrix &m) {
    int m_size = m.size(), sign = 1, A = 1;
    matrix nm = m;

    vector temp;
    for (int k = 0; k < m_size - 1; k++) {
        if (!nm[k][k]) {
            for (int i = k + 1; i < m_size; i++) {
                if (nm[i][k]) {
                    temp = nm[i];
                    nm[i] = nm[k];
                    nm[k] = temp;
                    sign *= -1;
                    break;
                }
            }
        }
        if (!nm[k][k]) return 0;

        for (int i = k + 1; i < m_size; i++) {
            for (int j = k + 1; j < m_size; j++) {
                nm[i][j] = (nm[i][j] * nm[k][k] - nm[i][k] * nm[k][j]) / A;
            }
        }
        A = nm[k][k];
    }

    return sign * nm[m_size - 1][m_size - 1];
}

void parallel::kramerSLAE(const matrix &m, const vector &b, vector &result) {
    int det = determinant(m), size = m.size();
    if (!det) return;

    matrix m2_t = m;

    #pragma omp parallel for firstprivate(m2_t)
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) m2_t[j][i] = b[j];
        result[i] = determinant(m2_t) / det;
        for (int j = 0; j < size; j++) m2_t[j][i] = m[j][i];
    }
}
