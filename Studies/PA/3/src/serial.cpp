#include <iostream>
#include <vector>
#include <omp.h>


// Generation functions

double** new_slae_matrix(int v_num) {
    double** matrix = new double*[v_num];
    for (int i = 0; i < v_num; i++) {
        matrix[i] = new double[v_num + 1];
        for (int j = 0; j < v_num; j++) matrix[i][j] = 1;
    }
    return matrix;
}

double** new_slae_matrix(int v_num, const double* xs) {
    double** matrix = new double*[v_num], result;
    for (int i = 0; i < v_num; i++) {
        matrix[i] = new double[v_num + 1];
        result = 0.0;
        for (int j = 0; j < v_num; j++) result += (matrix[i][j] = i + j) * xs[j];
        matrix[i][i] += 1;
        matrix[i][v_num] = result + xs[i];
    }
    return matrix;
}

void delete_slae_matrix(double** matrix, int v_num) {
    for (int i = 0; i < v_num; i++) delete[] matrix[i];
    delete[] matrix;
}

void print_matrix(const double* const* matrix, int h, int w) {
    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) std::printf("%6.2f  ", matrix[i][j]);
        std::printf("\n");
    }
}


// Algorithm functions

double determinant(const double* const* matrix, int y, std::vector<int> xs) {
    if (xs.size() == 2) return matrix[y][xs[0]] * matrix[y + 1][xs[1]] - matrix[y][xs[1]] * matrix[y + 1][xs[0]];
    double result = 0.0;
    std::vector<int> nxs;
    for (int i = 0; i < xs.size(); i += 2) {
        nxs = xs;
        nxs.erase(nxs.begin() + i);
        result += matrix[y][xs[i]] * determinant(matrix, y + 1, nxs);
    }
    for (int i = 1; i < xs.size(); i += 2) {
        nxs = xs;
        nxs.erase(nxs.begin() + i);
        result -= matrix[y][xs[i]] * determinant(matrix, y + 1, nxs);
    }
    return result;
}

void do_slae_with_kramer(const double* const* matrix, int v_num, double* result) {
    std::vector<int> xs = std::vector<int>(v_num);
    for (int i = 0; i < v_num; i++) xs[i] = i;
    double det = determinant(matrix, 0, xs);
    
    for (int i = 0; i < v_num; i++) {
        xs[i] = v_num;
        result[i] = determinant(matrix, 0, xs) / det;
        xs[i] = i;
    }
}


// Main

int main() {
    double *ex = new double[4], *x = new double[4];
    for (int i = 0; i < 4; i++) ex[i] = i;
    double **matrix = new_slae_matrix(4, ex);
    
    print_matrix(matrix, 4, 5);
    print_matrix(&ex, 1, 4);
    std::printf("%6.2f\n", determinant(matrix, 0, {0, 1, 2, 3}));
    
    do_slae_with_kramer(matrix, 4, x);
    
    std::printf("\n");
    print_matrix(matrix, 4, 5);
    print_matrix(&x, 1, 4);
    
    delete[] ex;
    delete[] x;
    delete_slae_matrix(matrix, 4);
    
    return 0;
}
