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

int distinct_num(const vi &xs) {
    int bits = 0;
    for (const int x : xs) {
        bits |= (1 << x);
    }
    return __builtin_popcount(bits);
}

int mpow(const int base, const int exp) {
    if (!exp) return 1;
    if (exp % 2) return base * mpow(base, exp - 1);
    const int q = mpow(base, exp / 2);
    return q * q;
}

struct DisjointDiceValues final {
    double getProbability(const int a, const int b) const {
        if (a > b) return getProbability(b, a);

        double ans = 0.0;
        const double denom_a = mpow(6, a);
        const double denom_b = mpow(6, b);
        vi xs(a, 1);

        do {
            ans += denom_b - mpow(6 - distinct_num(xs), b);
        } while (next_tuple(begin(xs), end(xs)));

        return ans / (denom_b * denom_a);
    }
};

#define forl(i, a, b) for (i = a; i < b; i++)

long long int dp[20][130][130];
int n, m;

bool iscommon(int m1, int m2) {
    int i;
    forl(i, 1, 7) {
        if ((m1 & (1 << i)) and (m2 & (1 << i))) return true;
    }
    return false;
}

long long int doit(int ind, int mask1, int mask2) {
    if (ind == n + m) {
        return iscommon(mask1, mask2);
    }
    if (dp[ind][mask1][mask2] != -1) return dp[ind][mask1][mask2];
    long long int ans = 0;
    // fill Alice's elements
    int i, j, k;
    if (ind < n) {
        forl(i, 1, 7) { ans += doit(ind + 1, mask1 | (1 << i), mask2); }
    } else { // fill Bob's elements
        forl(i, 1, 7) { ans += doit(ind + 1, mask1, mask2 | (1 << i)); }
    }

    dp[ind][mask1][mask2] = ans;
    return ans;
}
class Oracle {
  public:
    double getProbability(int A, int B) {
        long long int total = pow(6, A + B);
        n = A;
        m = B;
        int i, j, k, a, b;
        forl(i, 0, 20) {
            forl(k, 0, 130) {
                forl(a, 0, 130) { dp[i][k][a] = -1; }
            }
        }

        long long int r = doit(0, 0, 0);
        double ans = r;
        ans /= total;
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
        const auto expected = Oracle{}.getProbability(8, 8);
        EXPECT(abs(actual - expected) < 0.000001);
    },
    CASE("Example B") {
        const auto actual = DisjointDiceValues{}.getProbability(3, 4);
        const auto expected = Oracle{}.getProbability(3, 4);
        EXPECT(abs(actual - expected) < 0.000001);
    },
    CASE("Example C") {
        const auto actual = DisjointDiceValues{}.getProbability(1, 8);
        const auto expected = Oracle{}.getProbability(1, 8);
        EXPECT(abs(actual - expected) < 0.000001);
    },
    CASE("Example D") {
        const auto actual = DisjointDiceValues{}.getProbability(5, 2);
        const auto expected = Oracle{}.getProbability(5, 2);
        EXPECT(abs(actual - expected) < 0.000001);
    },
};
// clang-format on

int main(int argc, char **argv) { return lest::run(tests, argc, argv); }
