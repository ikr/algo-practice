#include "lest.hpp"
#include <bits/stdc++.h>
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

struct PickTwoMatch final {
    double chance(const vector<int> &xs) const {
        const int n = sz(xs);
        double m = 0.0;
        for (int i = 0; i < n - 1; ++i) {
            for (int j = i + 1; j < n; ++j) {
                m += xs[i] == xs[j];
            }
        }

        return m / (0.0 + n * (n - 1) / 2);
    }
};

static constexpr double EPS = 0.0000001;

// clang-format off
const lest::test tests[] = {
    CASE("Example 0") {
        const auto actual = PickTwoMatch{}.chance({1, 1, 1});
        const auto expected = 1.0;
        EXPECT(abs(actual - expected) < EPS);
    },
    CASE("Example 1") {
        const auto actual = PickTwoMatch{}.chance({ 1, 2, 2 });
        const auto expected = 0.3333333333333333;
        EXPECT(abs(actual - expected) < EPS);
    },
};
// clang-format on

int main(int argc, char **argv) { return lest::run(tests, argc, argv); }
