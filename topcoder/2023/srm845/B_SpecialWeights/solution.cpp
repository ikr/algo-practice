#include "lest.hpp"
#include <bits/stdc++.h>
using namespace std;

using ll = long long;

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

constexpr ll mlog2(const ll x) {
    if (!x) return 0;
    return 8LL * sizeof(ll) - __builtin_clzll(x) - 1LL;
}

struct SpecialWeights final {
    ll solve(const int N, const vector<ll> &xs, ll K) const {
        assert(sz(xs) == N);
        if (mlog2(K - 1) > N - 1) return -1;

        ll ans{};

        for (ll i = 0; i <= mlog2(K - 1); ++i) {
            if ((1LL << i) & (K - 1)) {
                ans += xs[i];
            }
        }

        return ans;
    }
};

// clang-format off
const lest::test tests[] = {
    CASE("Example 0") {
        const auto actual = SpecialWeights{}.solve(2, {4, 7}, 1);
        const auto expected = 0;
        EXPECT(actual == expected);
    },
    CASE("Example 1") {
        const auto actual = SpecialWeights{}.solve(2, {4, 7}, 4);
        const auto expected = 11;
        EXPECT(actual == expected);
    },
};
// clang-format on

int main(int argc, char **argv) { return lest::run(tests, argc, argv); }
