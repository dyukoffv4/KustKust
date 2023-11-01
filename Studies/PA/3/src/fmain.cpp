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
    if ((args.count("-P") + args.count("-I")) > 1) return 1;

    auto function = serial::kramerSLAE;
    int start = 10, stop = 160, step = 2, repeat = 10, cores = 4;

    if (args.count("-P")) {
        function = parallel::kramerSLAE;
        if (args["-P"].size() == 1 && (cores = std::stoi(args["-P"][0])) < 1) return 1;
        if (args["-P"].size() > 1) return 1;
        omp_set_num_threads(cores);
    }
    else if (args.count("-I")) {
        function = improved::kramerSLAE;
        if (args["-I"].size() == 1 && (cores = std::stoi(args["-I"][0])) < 1) return 1;
        if (args["-I"].size() > 1) return 1;
        omp_set_num_threads(cores);
    }

    if (args.count("-r") && (args["-r"].size() != 1 || (repeat = std::stoi(args["-r"][0])) < 1)) return 1;

    if (args.count("-d")) {
        if (args["-d"].size() > 0) start = stop = std::stoi(args["-d"][0]);
        if (args["-d"].size() > 1) stop = std::stoi(args["-d"][1]);
        if (args["-d"].size() > 2) step = std::stoi(args["-d"][2]);
        if (args["-d"].size() < 1 || args["-d"].size() > 3 || start < 2 || stop < 2 || step < 2) return 1;
    }

    // TESTS ARE BELOW

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
