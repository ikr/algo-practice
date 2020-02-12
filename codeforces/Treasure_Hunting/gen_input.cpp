#include <cstdlib>
#include <iostream>
#include <random>

constexpr int SIZE = 18000;

int main() {
    std::cout << SIZE << ' ' << SIZE << ' ' << SIZE << ' ' << SIZE << '\n';

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(1, SIZE);

    for (int i = 1; i <= SIZE; ++i) std::cout << i << ' ' << dist(gen) << '\n';

    for (int i = 1; i <= SIZE; ++i) {
        if (i > 1) std::cout << ' ';
        std::cout << i;
    }

    std::cout << '\n';
    return 0;
}
