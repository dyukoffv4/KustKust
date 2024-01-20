#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>
#include <thread>


// ---     types     ---

typedef std::vector<double> vector;
typedef std::vector<vector> matrix;


// ---   operators   ---

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


// --- kramer functions ---

double determinant(matrix m) {
    int m_size = m.size(), sign = 1;
    double A = 1.0, T;

    vector temp;
    for (int k = 0; k < m_size - 1; k++) {
        vector &mk = m[k];
        if (!mk[k]) {
            for (int i = k + 1; i < m_size; i++) {
                if (m[i][k]) {
                    temp = m[i];
                    m[i] = mk;
                    mk = temp;
                    sign *= -1;
                    break;
                }
            }
        }
        if (!(T = mk[k])) return 0;

        for (int i = k + 1; i < m_size; i++) {
            vector &mi = m[i];
            for (int j = k + 1; j < m_size; j++) mi[j] = (mi[j] * T - mi[k] * mk[j]) / A;
        }
        A = T;
    }

    return sign * m[m_size - 1][m_size - 1];
}

void part_kramer(const matrix& m, const vector &b, vector &result, int p0, int p1, double det) {
    int size = m.size();
    matrix tm = m;
    for (int i = p0; i < p1; i++) {
        for (int j = 0; j < size; j++) tm[j][i] = b[j];
        result[i] = determinant(tm) / det;
        for (int j = 0; j < size; j++) tm[j][i] = m[j][i];
    }
}

bool kramer(const matrix& m, const vector &b, vector &x, int nthr = 4) {
    double det;
    int size = m.size();
    if (size < 2 || size != m[0].size() || !(det = determinant(m))) return true;

    std::vector<std::thread> thrs;
    for (int i = 0; i < nthr; i++) {
        thrs.push_back(std::thread(part_kramer, std::ref(m), std::ref(b), std::ref(x), size * i / nthr, size * (i + 1) / nthr, det));
    }
    for (auto& i : thrs) i.join();
    return false;
}


// ---      main      ---

int main(int argc, char* argv[]) {
    if (argc == 2 || argc == 3) {
        std::ifstream in(argv[1]);
        if (in.is_open()) {
            int s;
            in >> s;
            matrix m(s, vector(s));
            vector b(s), x(s);

            for (int i = 0; i < s; i++) {
                for (int j = 0; j < s; j++) {
                    if (!(in >> m[i][j])) {
                        in.close();
                        std::cerr << "Invalid file format!\n";
                        return 1;
                    }
                }
                if (!(in >> b[i])) {
                    in.close();
                    std::cerr << "Invalid file format!\n";
                    return 1;
                }
            }
            in.close();

            if (kramer(m, b, x, 4)) {
                std::cerr << "Task can't be solved!\n";
                return 1;
            }

            int column = 2;
            if (argc == 3) column = std::atoi(argv[2]);
            if (column < 1) {
                std::cerr << "Invalid parametrs!\n";
                return 1;
            }

            int base_column_size = x.size() / column, drop_column_size = x.size() % column, index;
            for (int i = 0; i < base_column_size; i++) {
                for (int j = 0; j < column; j++) {
                    index = i + j * base_column_size + (j - drop_column_size < 0 ? j : drop_column_size);
                    std::printf("|x%i:\t%7.3f   ", index, x[index]);
                }
                std::printf("\n");
            }
            for (int j = 0; j < drop_column_size; j++) {
                index = base_column_size + j * (base_column_size + 1);
                std::printf("|x%i:\t%7.3f   ", index, x[index]);
            }
            std::printf("\n");

            return 0;
        }
        in.close();
        std::cerr << "File doesn't exist!\n";
        return 1;
    }
    std::cerr << "Invalid parametrs!\n";
    return 1;
}