#include "lest.hpp"
#include <iostream>
#include <vector>
using namespace std;

template <typename T> constexpr double doof(const T x) {
    return static_cast<double>(x);
}

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

static constexpr double EPS = 0.000001;

struct WeightedDice final {
    double winChance(const vector<double> &dist, const int T) const {
        vector<double> dp(T + 1, 0.0);
        dp[0] = 1.0;

        for (int i = 0; i < T; ++i) {
            for (int j = 0; j < sz(dist); ++j) {
                const auto delta = j + 1;
                const auto p = dist[j];

                if (i + delta <= T) {
                    dp[i + delta] += dp[i] * p;
                }
            }
        }

        return dp.back();
    }
};

// clang-format off
const lest::test tests[] = {
    CASE("Example 0") {
        const auto actual = WeightedDice{}.winChance({ 0.2, 0.2, 0.2, 0.2, 0.1, 0.1 }, 1);
        const auto expected = 0.2;
        EXPECT(abs(actual - expected) < EPS);
    },
    CASE("Example 1") {
        const auto actual = WeightedDice{}.winChance({ 0.2, 0.2, 0.2, 0.2, 0.1, 0.1 }, 2);
        const auto expected = 0.24;
        EXPECT(abs(actual - expected) < EPS);
    },
    CASE("Example 2") {
        const auto actual = WeightedDice{}.winChance({ 1.0, 0.0, 0.0, 0.0, 0.0, 0.0 }, 5);
        const auto expected = 1.0;
        EXPECT(abs(actual - expected) < EPS);
    },
    CASE("Example 3") {
        const auto actual = WeightedDice{}.winChance({ 0.5, 0.5, 0.0, 0.0, 0.0, 0.0 }, 3);
        const auto expected = 0.625;
        EXPECT(abs(actual - expected) < EPS);
    },
};
// clang-format on

int main(int argc, char **argv) { return lest::run(tests, argc, argv); }
