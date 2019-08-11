#include <cstdlib>
#include <iostream>
#include <random>

int main() {
    std::cout << "10000 10000 10000 10000\n";

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(1, 10000);

    for (int i = 1; i <= 10000; ++i) std::cout << i << ' ' << dist(gen) << '\n';

    for (int i = 1; i <= 10000; ++i) {
        if (i > 1) std::cout << ' ';
        std::cout << i;
    }

    std::cout << '\n';
    return 0;
}
