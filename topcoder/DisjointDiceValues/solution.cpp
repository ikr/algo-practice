#include "lest.hpp"
#include <bits/stdc++.h>
using namespace std;

using vi = vector<int>;
using Iter = vi::iterator;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

bool next_tuple(const Iter first, const Iter last) {
    if (first == last) return false;

    if (*first < 6) {
        ++(*first);
        return true;
    }

    if (next_tuple(next(first), last)) {
        *first = 1;
        return true;
    }

    return false;
}

int distinct_num(const vi &xs) { return sz(set<int>(xs.cbegin(), xs.cend())); }

int mpow(const int base, const int exp) {
    if (!exp) return 1;
    if (exp % 2) return base * mpow(base, exp - 1);
    const int q = mpow(base, exp / 2);
    return q * q;
}

double prob_num_values_dont_occur(const int b, const int num) {
    const double denom = mpow(6, b);
    const double numer = mpow(6 - num, b);
    return numer / denom;
}

struct DisjointDiceValues final {
    double getProbability(const int a, const int b) const {
        if (a > b) return getProbability(b, a);

        double ans = 0.0;
        const double denom = mpow(6, a);
        vi xs(a, 1);

        do {
            ans +=
                (1.0 - prob_num_values_dont_occur(b, distinct_num(xs))) / denom;
        } while (next_tuple(begin(xs), end(xs)));

        return ans;
    }
};

// clang-format off
const lest::test tests[] = {
    CASE("Example 0") {
        const auto actual = DisjointDiceValues{}.getProbability(1, 1);
        const auto expected =  0.16666666666666663;
        EXPECT(abs(actual - expected) < 0.000001);
    },
    CASE("Example 1") {
        const auto actual = DisjointDiceValues{}.getProbability(4, 1);
        const auto expected = 0.5177469135802468;
        EXPECT(abs(actual - expected) < 0.000001);
    },
    CASE("Example 2") {
        const auto actual = DisjointDiceValues{}.getProbability(1, 4);
        const auto expected = 0.5177469135802468;
        EXPECT(abs(actual - expected) < 0.000001);
    },
    CASE("Example 3") {
        const auto actual = DisjointDiceValues{}.getProbability(3, 3);
        const auto expected = 0.7910236625514401;
        EXPECT(abs(actual - expected) < 0.000001);
    },
    CASE("Example A") {
        const auto actual = DisjointDiceValues{}.getProbability(8, 8);
        const auto expected = 0.999585;
        EXPECT(abs(actual - expected) < 0.000001);
    },
};
// clang-format on

int main(int argc, char **argv) { return lest::run(tests, argc, argv); }
