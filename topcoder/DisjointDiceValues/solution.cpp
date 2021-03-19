#include "lest.hpp"
#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vi = vector<int>;
using vvi = vector<vi>;
using pii = pair<int, int>;
using vll = vector<ll>;
using vvll = vector<vll>;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}
template <typename T> constexpr ll llof(const T x) {
    return static_cast<ll>(x);
}
template <typename T> constexpr double doof(const T x) {
    return static_cast<double>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

ll factorial(const ll x) {
    assert(x >= 0);
    if (x <= 1) return 1;

    ll ans = 2;
    for (ll i = 3; i <= x; ++i) {
        ans *= i;
        ans %= M;
    }

    return ans;
}

ll product_of_range(const ll a, const ll b) {
    ll ans = 1;
    for (ll x = a; x <= b; ++x) {
        ans *= x;
        ans %= M;
    }
    return ans;
}

ll combinations(const ll n, const ll k) {
    assert(k <= n);
    const ll r = n - k;
    const ll ans = r < k
                       ? product_of_range(k + 1, n) * inv_mod(factorial(r), M)
                       : product_of_range(r + 1, n) * inv_mod(factorial(k), M);
    return ans % M;
}

struct DisjointDiceValues final {
    double getProbability(const int a, const int b) const { return 42; }
};

// clang-format off
const lest::test tests[] = {
    CASE("Example 0") {
        const auto actual = DisjointDiceValues{}.getProbability(1, 1);
        const auto expected =  0.16666666666666663;
        EXPECT(abs(actual - expected) < 0.0000001);
    },
    CASE("Example 1") {
        const auto actual = DisjointDiceValues{}.getProbability(4, 1);
        const auto expected = 0.5177469135802468;
        EXPECT(abs(actual - expected) < 0.0000001);
    },
    CASE("Example 2") {
        const auto actual = DisjointDiceValues{}.getProbability(1, 4);
        const auto expected = 0.5177469135802468;
        EXPECT(abs(actual - expected) < 0.0000001);
    },
    CASE("Example 3") {
        const auto actual = DisjointDiceValues{}.getProbability(3, 3);
        const auto expected = 0.7910236625514401;
        EXPECT(abs(actual - expected) < 0.0000001);
    },
};
// clang-format on

int main(int argc, char **argv) { return lest::run(tests, argc, argv); }
