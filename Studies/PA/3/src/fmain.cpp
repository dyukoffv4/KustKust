#include "serial.hpp"
#include "improved.hpp"
#include "parallel.hpp"
#include <string>
#include <map>

int main(int argc, char* argv[]) {
    std::map<std::string, std::vector<std::string>> args;
    for (int i = 1, j = 1; i < argc; i++) {
        if (argv[i][0] == '-') args[argv[j = i]] = {};
        else args[argv[j]].push_back(argv[i]);
    }
    if (args.size() < 1 || (args.count("-S") + args.count("-P") + args.count("-I")) != 1) return 1;

    auto function = args.count("-S") ? serial::kramerSLAE : (args.count("-P") ? parallel::kramerSLAE : improved::kramerSLAE);
    int start = 10, stop = 160, step = 2, repeat = 10;

    if (args.count("-r") && args["-r"].size() == 1) {
        repeat = std::stoi(args["-r"][0]);
        if (repeat < 1) return 1;
    }

    if (args.count("-d") && args["-d"].size() == 3) {
        start = std::stoi(args["-d"][0]);
        stop = std::stoi(args["-d"][1]);
        step = std::stoi(args["-d"][2]);
        if (start < 2 || stop < 2 || step < 2) return 1;
    }

    matrix m;
    vector x, b;
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
