#include "shared.hpp"
#include <omp.h>

namespace improved {
    int determinant(const matrix &);

    void kramerSLAE(const matrix &, const vector &, vector &);
}
