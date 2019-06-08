#include <cstdlib>
#include <iostream>
#include <random>

int main(int argc, char **argv) {
    if (argc != 3) {
        std::cerr << "Usage: ./gen_input <MAX COORD VALUE> <POINTS COUNT>" << '\n';
        return 1;
    }

    const int max_coord = std::atoi(argv[1]);
    const int n = std::atoi(argv[2]);
    std::cout << n << std::endl;

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(-max_coord, max_coord);

    for (int i = 0; i != n; ++i)
        std::cout << dist(gen) << ' ' << dist(gen) << '\n';

    return 0;
}
