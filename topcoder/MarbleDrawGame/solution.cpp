#include "lest.hpp"
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

ll factorial(const ll x) {
    assert(x >= 0);
    if (x <= 1) return 1;

    ll ans = 2;
    for (ll i = 3; i <= x; ++i) {
        ans *= i;
    }
    assert(ans > 0LL);
    return ans;
}

ll product_of_range(const ll a, const ll b) {
    ll ans = 1;
    for (ll x = a; x <= b; ++x) ans *= x;
    assert(ans > 0LL);
    return ans;
}

ll combinations(const ll n, const ll k) {
    assert(k <= n);
    const ll r = n - k;
    return r < k ? product_of_range(k + 1, n) / factorial(r)
                 : product_of_range(r + 1, n) / factorial(k);
}

template <typename T> constexpr double doof(const T x) {
    return static_cast<double>(x);
}

struct MarbleDrawGame final {
    double winningChance(const vector<int> &xs) const {
        const ll m = accumulate(xs.cbegin(), xs.cend(), 0);
        const ll denom = combinations(m, 9);

        ll t_num = 0LL;

        for (const int x : xs) {
            for (const int s : {5, 6, 7, 8, 9}) {
                if (x < s) break;
                t_num += combinations(x, s) * combinations(m - x, 9 - s);
            }
        }

        return doof(t_num) / doof(denom);
    }
};

// clang-format off
const lest::test tests[] = {
    CASE("Combi 10 of 10") {
        const auto actual = combinations(10, 10);
        const auto expected = 1LL;
        EXPECT(actual == expected);
    },
    CASE("Combi 10 of 1") {
        const auto actual = combinations(10, 1);
        const auto expected = 10LL;
        EXPECT(actual == expected);
    },
    CASE("Combi 52 of 5") {
        const auto actual = combinations(52, 5);
        const auto expected = 2598960LL;
        EXPECT(actual == expected);
    },
    CASE("Example 0") {
        const auto actual = MarbleDrawGame{}.winningChance({5, 5});
        const auto expected = 1.0;
        EXPECT(abs(actual - expected) < 1e-9);
    },
    CASE("Example 1") {
        const auto actual = MarbleDrawGame{}.winningChance({3, 4, 3});
        const auto expected = 0.0;
        EXPECT(abs(actual - expected) < 1e-9);
    },
    CASE("Example 2") {
        const auto actual = MarbleDrawGame{}.winningChance({1, 1, 1, 1, 1, 5});
        const auto expected = 0.5;
        EXPECT(abs(actual - expected) < 1e-9);
    },
    CASE("Example 3") {
        const auto actual = MarbleDrawGame{}.winningChance({3, 4, 5, 6});
        const auto expected = 0.08031674208144797;
        EXPECT(abs(actual - expected) < 1e-9);
    },
};
// clang-format on

int main(int argc, char **argv) { return lest::run(tests, argc, argv); }
