#include "shared.hpp"
#include <omp.h>

namespace serial {
    int determinant(const matrix &);

    void kramerSLAE(const matrix &, const vector &, vector &);
}
