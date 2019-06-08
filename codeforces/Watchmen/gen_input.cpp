#include <cstdlib>
#include <iostream>
#include <random>

constexpr int MAX_COORD = 1000 * 1000 * 1000;
constexpr int MIN_COORD = -MAX_COORD;

int main(int argc, char **argv) {
    if (argc != 2) {
        std::cerr << "Usage: ./gen_input <POINTS COUNT>" << '\n';
        return 1;
    }

    const int n = std::atoi(argv[1]);
    std::cout << n << std::endl;

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(MIN_COORD, MAX_COORD);

    for (int i = 0; i != n; ++i)
        std::cout << dist(gen) << ' ' << dist(gen) << '\n';

    return 0;
}
