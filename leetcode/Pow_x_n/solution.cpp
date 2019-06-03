#include "lest.hpp"
#include <bits/stdc++.h>

using namespace std;

struct Solution final {
    double myPow(const double x, const int n) { return x * n; }
};

// clang-format off
const lest::test tests[] = {
    CASE("42^0") {
        const auto actual = Solution().myPow(42.0, 0);
        const auto expected = lest::approx(1.0);
        EXPECT(actual == expected);
    },
    CASE("-42^0") {
        const auto actual = Solution().myPow(-42.0, 0);
        const auto expected = lest::approx(1.0);
        EXPECT(actual == expected);
    },
    CASE("-2^-2") {
        const auto actual = Solution().myPow(-2.0, -2);
        const auto expected = lest::approx(0.5);
        EXPECT(actual == expected);
    },
    CASE("-2^3") {
        const auto actual = Solution().myPow(-2.0, 3);
        const auto expected = lest::approx(-8.0);
        EXPECT(actual == expected);
    },
    CASE("1^1") {
        const auto actual = Solution().myPow(1.0, 1);
        const auto expected = lest::approx(1.0);
        EXPECT(actual == expected);
    },
    CASE("1^-1") {
        const auto actual = Solution().myPow(1.0, -1);
        const auto expected = lest::approx(1.0);
        EXPECT(actual == expected);
    },
    CASE("-1^-1") {
        const auto actual = Solution().myPow(-1.0, -1);
        const auto expected = lest::approx(-1.0);
        EXPECT(actual == expected);
    },
    CASE("1^999999") {
        const auto actual = Solution().myPow(1.0, 999999);
        const auto expected = lest::approx(1.0);
        EXPECT(actual == expected);
    },
    CASE("2^16") {
        const auto actual = Solution().myPow(2.0, 16);
        const auto expected = lest::approx(65536.0);
        EXPECT(actual == expected);
    },
    CASE("0^-1") {
        const auto actual = Solution().myPow(0.0, -1);
        const auto expected = lest::approx(INFINITY);
        EXPECT(actual == expected);
    },
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
