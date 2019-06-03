#include "lest.hpp"
#include <bits/stdc++.h>

using namespace std;

constexpr double epsilon = 1.0 / (1000.0 * 1000.0);
bool approx(const double x, const double y) { return abs(x - y) < epsilon; }

double sign(const double x, const int n) {
    if (x >= 0) return 1.0;
    return abs(n) % 2 ? -1.0 : 1.0;
}

double pow_positive(const double x, const int n) {
    assert(x > 0);
    assert(n > 0);

    if (n == 1) return x;
    if (n % 2) return x * pow_positive(x, n - 1);

    double sqrt = pow_positive(x, n / 2);
    return sqrt * sqrt;
}

struct Solution final {
    double myPow(const double x, const int n) const {
        if (approx(x, 0.0)) {
            if (!n) return 1.0;
            return n > 0 ? 0.0 : INFINITY;
        }

        if (!n) return 1.0;
        if (approx(x, 1.0)) return sign(x, n);
        if (n == INT_MIN) return 0.0;

        return (n < 0 ? sign(x, n) * (1.0 / pow_positive(abs(x), -n))
                      : sign(x, n) * pow_positive(abs(x), n));
    }
};

// clang-format off
const lest::test tests[] = {
    CASE("0^0") {
        const auto actual = Solution().myPow(0.0, 0);
        const auto expected = lest::approx(1.0);
        EXPECT(actual == expected);
    },
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
        const auto expected = lest::approx(0.25);
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
    CASE("-1^-100") {
        const auto actual = Solution().myPow(-1.0, -100);
        const auto expected = lest::approx(1.0);
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
        const auto expected = INFINITY;
        EXPECT(actual == expected);
    },
    CASE("0^100") {
        const auto actual = Solution().myPow(0.0, 100);
        const auto expected = lest::approx(0.0);
        EXPECT(actual == expected);
    },
    CASE("9.31^15") {
        const auto actual = Solution().myPow(9.31, 15);
        const auto expected = lest::approx(342172588122574.6);
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
    CASE("2^-2147483648") {
        const auto actual = Solution().myPow(2.0, -2147483648);
        const auto expected = lest::approx(0.0);
        EXPECT(actual == expected);
    },
    CASE("2^2147483647") {
        const auto actual = Solution().myPow(2.0, 2147483647);
        const auto expected = INFINITY;
        EXPECT(actual == expected);
    },
    CASE("-2^-2147483648") {
        const auto actual = Solution().myPow(2.0, -2147483648);
        const auto expected = lest::approx(0.0);
        EXPECT(actual == expected);
    },
    CASE("-2^2147483647") {
        const auto actual = Solution().myPow(-2.0, 2147483647);
        const auto expected = -INFINITY;
        EXPECT(actual == expected);
    },
};
// clang-format on

int main(int argc, char **argv) { return lest::run(tests, argc, argv); }
