#include "serial.hpp"
#include "improved.hpp"
#include "parallel.hpp"

int main() {
    std::printf("--> Setup <--\n\n");
    std::printf("Enter type of function you want to test. (1. Serial  |  2. Parallel  |  3. Improved) -> ");
    int setup;
    std::cin >> setup;
    if (setup < 1 || setup > 3) return 1;
    auto function = setup == 1 ? serial::kramerSLAE : (setup == 2 ? parallel::kramerSLAE : improved::kramerSLAE);

    if (setup > 1) {
        std::printf("\nEnter number of process. (expected number, default - 4) -> ");
        std::cin >> setup;
        if (setup < 1) omp_set_num_threads(4);
        else omp_set_num_threads(setup);
    }

    int start = 10, stop = 160, step = 2;
    std::printf("\nCurrent numbers for a range of number of variables for SLAE are: start = %d, stop = %d, step = %d", start, stop, step);
    std::printf("\nDo you want to change this settings? (1. YES  |  0. NO) -> ");
    std::cin >> setup;
    if (setup) {
        std::printf("\nEnter start, stop and step numbers for a range of number of variables for SLAE (expected 3 numbers, bigger than 1):\n");
        std::cin >> start >> stop >> step;
        if (start < 2 || stop < 2 || step < 2) return 1;
    }

    std::printf("\nEnter number of timetests for one number of variables. (expected number, default - 10) -> ");
    int repeat;
    std::cin >> repeat;
    if (repeat < 1) repeat = 10;
    
    matrix m;
    vector x, b;
    std::printf("\nDo you want to see presentation of work of programm for SLAE for %d variables? (1. YES  |  0. NO) -> ", start);
    std::cin >> setup;

    if (setup) {
        m = get_matrix(start);
        b = m * (x = get_vector(start, 0, start));

        std::cout << "\nSLAE:\n";
        for (int i = 0; i < start; i++) std::cout << m[i] << " |   " << b[i] << "\n";
        std::cout << "\nExpected: " << x;
        function(m, b, x);
        std::cout << "\nActual:   " << x;
    }
    std::cout << "\n\n";

    // Time test
    std::cout << "--> Time test <--\n\n";
    double t_point, t_medium;
    for (int i = start; i <= stop; i *= step) {
        m = get_matrix(i);
        b = m * get_vector(i, 0, i);
        x = get_vector(i, 0);

        t_medium = 0;
        for (int j = 0; j < repeat; j++) {
            t_point = omp_get_wtime();
            function(m, b, x);
            t_medium += (omp_get_wtime() - t_point) * 1000;
        }
        
        if (x != get_vector(i, 0, i)) std::cout << "Wrong answer below!\n";
        std::printf("Variables: %4d\t\tTime (ms): %10.3f\n", i, t_medium / repeat);
    }

    return 0;
}