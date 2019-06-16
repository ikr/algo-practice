#include <cstdlib>
#include <iostream>
#include <random>

int main(int argc, char **argv) {
    if (argc != 2) {
        std::cerr << "Usage: ./gen_input <DIGITS COUNT>" << '\n';
        return 1;
    }

    const int digits_count = std::atoi(argv[1]);
    std::cout << digits_count << '\n';

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(0, 9);

    for (int i = 0; i != digits_count; ++i) std::cout << dist(gen);

    std::cout << '\n';
    return 0;
}
