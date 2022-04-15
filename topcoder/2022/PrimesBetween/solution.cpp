#include "lest.hpp"
#include <iostream>
using namespace std;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

template <typename T> constexpr typename T::const_iterator xbegin(const T &xs) {
    return xs.cbegin();
}

template <typename T> constexpr typename T::const_iterator xend(const T &xs) {
    return xs.cend();
}

bool is_prime(const int x) {
    if (x == 1) return false;
    for (int i = 2; i * i <= x; ++i) {
        if (x % i == 0) return false;
    }
    return true;
}

struct PrimesBetween final {
    int count(const int a, const int b) const {
        int result{};
        for (int i = a; i <= b; ++i) {
            if (is_prime(i)) ++result;
        }
        return result;
    }
};

// clang-format off
const lest::test tests[] = {
    CASE("Example 0") {
        const auto actual = PrimesBetween{}.count(2, 11);
        const auto expected = 5;
        EXPECT(actual == expected);
    },
    CASE("Example 1") {
        const auto actual = PrimesBetween{}.count(8, 10);
        const auto expected = 0;
        EXPECT(actual == expected);
    },
    CASE("Example 2") {
        const auto actual = PrimesBetween{}.count(12, 20);
        const auto expected = 3;
        EXPECT(actual == expected);
    },
    CASE("Example 3") {
        const auto actual = PrimesBetween{}.count(20, 30);
        const auto expected = 2;
        EXPECT(actual == expected);
    },
    CASE("Example A") {
        const auto actual = PrimesBetween{}.count(1, 2);
        const auto expected = 1;
        EXPECT(actual == expected);
    },
};
// clang-format on

int main(int argc, char **argv) { return lest::run(tests, argc, argv); }
