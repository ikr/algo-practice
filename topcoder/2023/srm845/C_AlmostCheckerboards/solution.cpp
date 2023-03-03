#include "lest.hpp"
#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vll = vector<ll>;
using vvll = vector<vll>;

static constexpr ll M = 1e9 + 7;

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

vvll combinations(const int n, const int k) {
    assert(k <= n);
    vvll ans(n + 1, vll(k + 1, 1));

    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= min(i, k); ++j) {
            ans[i][j] = i == j ? 1 : ans[i - 1][j - 1] + ans[i - 1][j];
            ans[i][j] %= M;
        }
    }

    return ans;
}

struct AlmostCheckerboards final {
    int count(const int R, const int C, const int D) const {
        if (R * C / 2 < D) return 0;

        const auto cs = combinations(R * C, R * C);
        const auto i_choose_j = [&cs](const int i, const int j) -> ll {
            assert(j <= i);
            return cs[i][j];
        };

        ll ans = 2LL * i_choose_j(R * C, D);
        ans %= M;
        return inof(ans);
    }
};

// clang-format off
const lest::test tests[] = {
    CASE("Example 0") {
        const auto actual = AlmostCheckerboards{}.count(3, 4, 47);
        const auto expected = 0;
        EXPECT(actual == expected);
    },
    CASE("Example 1") {
        const auto actual = AlmostCheckerboards{}.count(2, 2, 1);
        const auto expected = 8;
        EXPECT(actual == expected);
    },
};
// clang-format on

int main(int argc, char **argv) { return lest::run(tests, argc, argv); }
