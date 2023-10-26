#include "shared.hpp"
#include <omp.h>


long determinant(const matrix &m) {
    int m_size = m.size(), e_size = m.size() + 1, sign = 1;

    matrix nm(e_size, vector(e_size, 1));
    for (int i = 0; i < m_size; i++) for (int j = 0; j < m_size; j++) nm[i + 1][j + 1] = m[i][j];

    // Main diagonal without zeros
    vector temp;
    for (int k = 1; k < e_size - 1; k++) {
        if (!nm[k][k]) {
            for (int i = k + 1; i < e_size; i++) {
                if (nm[i][k - 1]) {
                    temp = nm[i];
                    nm[i] = nm[k];
                    nm[k] = temp;
                    sign *= -1;
                    break;
                }
            }
            if (!nm[k - 1][k - 1]) return 0;
        }
    }

    // Bareis method
    for (int k = 1; k < e_size - 1; k++) {
        for (int i = k + 1; i < e_size; i++) {
            for (int j = k + 1; j < e_size; j++) {
                nm[i][j] = (nm[i][j] * nm[k][k] - nm[i][k] * nm[k][j]) / nm[k - 1][k - 1];
            }
        }
    }

    return sign * nm[m_size][m_size];
}

void kramerSLAE(const matrix &m, vector &result) {
    matrix m2(m.size(), vector(m.size()));
    for (int i = 0; i < m.size(); i++) for (int j = 0; j < m.size(); j++) m2[i][j] = m[i][j];

    vector b(m.size());
    for (int i = 0; i < m.size(); i++) b[i] = m[i][m.size()];

    long det = determinant(m2);

    matrix m2_t = m2;
    for (int i = 0; i < m.size(); i++) {
        for (int j = 0; j < m.size(); j++) m2_t[i][j] = b[j];
        result[i] = determinant(m2_t) / det;
        for (int j = 0; j < m.size(); j++) m2_t[i][j] = m2[i][j];
    }
}


int main() {
    double t_point;
    vector ex(5), x(5);
    for (int j = 0; j < 5; j++) ex[j] = j;
    matrix m = matrixSLAE(ex);

    std::cout << "Work test:\nSLAE for 5 variables:\n" << m << '\n';
    std::cout << "Expected: " << ex;
    kramerSLAE(m, x);
    std::cout << "Actual:   " << x << "\n\n";

    std::cout << "Timetests:\n\n";
    for (int i = 5; i <= 625; i *= 5) {
        ex = x = vector(i);
        for (int j = 0; j < i; j++) ex[j] = j;
        m = matrixSLAE(ex);

        t_point = omp_get_wtime();
        kramerSLAE(m, x);
        t_point = (omp_get_wtime() - t_point) * 1000;
        
        for (int j = 0; j < i; j++) {
            if (x[j] != j) {
                std::cout << "Wrong answer below!\n";
                break;
            }
        }

        std::printf("Variables: %3d\t\tTime (ms): %10.3f\n", i, t_point);
    }

    return 0;
}
