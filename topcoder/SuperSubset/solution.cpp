#include "lest.hpp"
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
static constexpr ll M = 1e9 + 7;

ll factorial_mod(const ll x, const ll m) {
    assert(x >= 0);
    if (x <= 1) return 1;

    ll ans = 2;
    for (ll i = 3; i <= x; ++i) {
        ans *= i;
        ans %= m;
    }

    assert(ans > 0LL);
    return ans;
}

constexpr ll pow_mod(const ll base, const ll exp, const ll m) {
    if (!exp) return 1;
    if (exp % 2) return (base * pow_mod(base, exp - 1, m)) % m;
    const ll q = pow_mod(base, exp / 2, m);
    return (q * q) % m;
}

struct SuperSubset final {
    int solve(vector<int> xs, const int y) const {
        sort(begin(xs), end(xs));
        const int n = xs.size();

        vector<int> ss(n + 1, 0);
        partial_sum(xs.cbegin(), xs.cend(), next(begin(ss)));

        int lo = 0;
        int hi = 0;
        ll ans = 0;

        while (lo < n && hi < n) {
            const int s = ss[hi + 1] - ss[lo];

            if (s == y) {
                const int d = hi - lo + 1;
                const int r = n - d;
                ans += factorial_mod(d, M) * pow_mod(2LL, r, M);
                ans %= M;

                ++lo;
                if (hi < lo) hi = lo;
            } else if (s < y) {
                ++hi;
            } else {
                assert(s > y);
                ++lo;
                if (hi < lo) hi = lo;
            }
        }

        return ans;
    }
};

// clang-format off
const lest::test tests[] = {
    CASE("Example 0") {
        const auto actual = SuperSubset{}.solve({1, 2, 3}, 3);
        const auto expected = 6;
        EXPECT(actual == expected);
    },
    CASE("Example 1") {
        const auto actual = SuperSubset{}.solve({1, 1, 1, 1, 1}, 4);
        const auto expected = 10;
        EXPECT(actual == expected);
    },
};
// clang-format on

int main(int argc, char **argv) { return lest::run(tests, argc, argv); }
