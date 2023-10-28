#include "shared.hpp"
#include <omp.h>

namespace parallel {
    int determinant(const matrix &);

    void kramerSLAE(const matrix &, const vector &, vector &);
}
