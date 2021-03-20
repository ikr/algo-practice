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
    }

    return ans;
}

ll product_of_range(const ll a, const ll b) {
    ll ans = 1;
    for (ll x = a; x <= b; ++x) ans *= x;
    return ans;
}

ll combinations(const ll n, const ll k) {
    assert(k <= n);
    const ll r = n - k;
    const ll ans = r < k ? product_of_range(k + 1, n) / factorial(r)
                         : product_of_range(r + 1, n) / factorial(k);
    return ans;
}

ll mpow(const ll base, const ll exp) {
    if (!exp) return 1;
    if (exp % 2) return mpow(base, exp - 1);
    const ll q = mpow(base, exp / 2);
    return q * q;
}

double prob_at_least_one(const int dice_num) {
    double ans = 0.0;

    for (int n = 1; n <= dice_num; ++n) {
        ans += doof(combinations(dice_num, n) * mpow(5, dice_num - n)) /
               doof(mpow(6, dice_num));
    }

    return ans;
}

struct DisjointDiceValues final {
    double getProbability(const int a, const int b) const {
        cout << "a:" << a << " prob:" << prob_at_least_one(a) << '\n';
        cout << "b:" << b << " prob:" << prob_at_least_one(b) << '\n';
        return 6.0 * prob_at_least_one(a) * prob_at_least_one(b);
    }
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
