#include "lest.hpp"
#include <array>
#include <cmath>
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

using Game = array<int, 7>;

int exact_games_num(const int T) {
    const auto recur = [&](const auto self, const int d, const int t) -> int {
        if (t < 0) return 0;
        if (t == 0) return 1;
        if (d < 1) return 0;

        return self(self, d, t - d) + self(self, d - 1, t);
    };

    return recur(recur, 6, T);
}

struct WeightedDice final {
    double winChance(const vector<double> &P, const int T) const {
        const double A = exact_games_num(T);
        double B = exact_games_num(T - 1) + P[1] + P[2] + P[3] + P[4] + P[5];
        if (exact_games_num(T - 2)) {
            B += exact_games_num(T - 2) + P[2] + P[3] + P[4] + P[5];
        }
        if (exact_games_num(T - 3)) {
            B += exact_games_num(T - 3) + P[3] + P[4] + P[5];
        }
        if (exact_games_num(T - 4)) {
            B += exact_games_num(T - 4) + P[4] + P[5];
        }
        if (exact_games_num(T - 5)) {
            B += exact_games_num(T - 5) + P[5];
        }

        return A / B;
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
