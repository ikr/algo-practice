#include <iostream>

int main() {
    int A, I;
    std::cin >> A >> I;

    const auto ans = A * I - (A - 1);
    std::cout << ans << '\n';
    return 0;
}
