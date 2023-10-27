#include "shared.hpp"
#include <omp.h>


int determinant(const matrix &m) {
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

void kramerSLAE(const matrix &m, const vector &b, vector &result) {
    int det = determinant(m), size = m.size();
    if (det == 0) {
        std::cout << "Determinant equal to 0!\n";
        return;
    }

    matrix m2_t = m;

    #pragma omp parallel for firstprivate(m2_t)
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) m2_t[j][i] = b[j];
        result[i] = determinant(m2_t) / det;
        for (int j = 0; j < size; j++) m2_t[j][i] = m[j][i];
    }
}


int main() {
    omp_set_num_threads(4);

    double t_point, t_medium;
    int start = 4, step = 4, end = 256, repeat = 10;

    matrix m = get_matrix(start);
    vector x = get_vector(start), b = m * x;

    // Work test
    std::printf("Work test:\nSLAE for %2d variables:\n", start);
    for (int i = 0; i < start; i++) std::cout << m[i] << " |   " << b[i] << "\n";
    std::cout << "\nExpected: " << x;
    kramerSLAE(m, b, x);
    std::cout << "\nActual:   " << x << "\n\n";

    // Time test
    std::cout << "Time test:\n\n";
    for (int i = start; i <= end; i *= step) {
        m = get_matrix(i);
        b = m * get_vector(i);
        x = get_vector(i, 0);

        t_medium = 0;
        for (int j = 0; j < repeat; i++) {
            t_point = omp_get_wtime();
            kramerSLAE(m, b, x);
            t_medium += (omp_get_wtime() - t_point) * 1000;
        }
        
        if (x != get_vector(i)) std::cout << "Wrong answer below!\n";
        std::printf("Variables: %4d\t\tTime (ms): %10.3f\n", i, t_medium / repeat);
    }

    return 0;
}
