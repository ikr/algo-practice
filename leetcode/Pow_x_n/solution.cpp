#include "lest.hpp"
#include <bits/stdc++.h>

using namespace std;

struct Solution final {
    double myPow(double x, int n) { return x * n; }
};

// clang-format off
const lest::test tests[] = {
    CASE("problem statement example 1") {
        const auto actual = Solution().myPow(2.0, 10);
        const auto expected = lest::approx(1024.0);
        EXPECT(actual == expected);
    },
    CASE("problem statement example 2") {
        const auto actual = Solution().myPow(2.1, 3);
        const auto expected = lest::approx(9.261);
        EXPECT(actual == expected);
    },
    CASE("problem statement example 3") {
        const auto actual = Solution().myPow(2.0, -2);
        const auto expected = lest::approx(0.25);
        EXPECT(actual == expected);
    },
};
// clang-format on

int main(int argc, char **argv) { return lest::run(tests, argc, argv); }
