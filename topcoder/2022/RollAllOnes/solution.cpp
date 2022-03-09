#include "lest.hpp"
#include <algorithm>
#include <cmath>
#include <iostream>
using namespace std;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr double doof(const T x) {
    return static_cast<double>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

template <typename T> constexpr typename T::const_iterator xbegin(const T &xs) {
    return xs.cbegin();
}

template <typename T> constexpr typename T::const_iterator xend(const T &xs) {
    return xs.cend();
}

struct RollAllOnes final {
    double solve(const int N, const int D) const {
        double result = N * D;
        cerr << "result0: " << result << endl;

        for (int i = N; i >= 1; --i) {
            const auto q = N / i;
            const auto r = N % i;

            const auto candidate = q * pow(doof(D), i) + r * doof(D);
            cerr << "candidate: " << candidate << endl;
            result = min(result, candidate);
        }

        return result;
    }
};

static constexpr double EPS = 0.00000001;

// clang-format off
const lest::test tests[] = {
    CASE("Example 0") {
        const auto actual = RollAllOnes{}.solve(1, 6);
        const auto expected = 6.0;
        EXPECT(abs(actual - expected) < EPS);
    },
    CASE("Example 1") {
        const auto actual = RollAllOnes{}.solve(2, 2);
        const auto expected = 2.666666666666666;
        EXPECT(abs(actual - expected) < EPS);
    },
    CASE("Example 2") {
        const auto actual = RollAllOnes{}.solve(3, 10);
        const auto expected = 17.900563216158464;
        EXPECT(abs(actual - expected) < EPS);
    },
};
// clang-format on

int main(int argc, char **argv) { return lest::run(tests, argc, argv); }
