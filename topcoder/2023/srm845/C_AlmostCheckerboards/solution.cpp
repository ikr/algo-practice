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

ll pow_mod(const ll base, const ll exp, const ll m) {
    if (!exp) return 1;
    if (exp % 2LL) return (base * pow_mod(base, exp - 1, m)) % m;
    const ll q = pow_mod(base, exp / 2, m);
    return (q * q) % m;
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

        ll ans = i_choose_j(R * C, D);
        if (R * C != 2 * D) ans *= 2;
        ans %= M;
        return inof(ans);
    }
};

// clang-format off
const lest::test tests[] = {
    CASE("Example 0") {
        const auto actual = AlmostCheckerboards{}.count(3, 4, 0);
        const auto expected = 2;
        EXPECT(actual == expected);
    },
    CASE("Example 1") {
        const auto actual = AlmostCheckerboards{}.count(3, 4, 47);
        const auto expected = 0;
        EXPECT(actual == expected);
    },
    CASE("Example 2") {
        const auto actual = AlmostCheckerboards{}.count(2, 2, 1);
        const auto expected = 8;
        EXPECT(actual == expected);
    },
    CASE("Example 3") {
        const auto actual = AlmostCheckerboards{}.count(9, 4, 15);
        const auto expected = 135805043;
        EXPECT(actual == expected);
    },
    CASE("Test the total number of possible boards sums up to 2^(R*C)") {
        const auto R = 17;
        const auto C = 19;

        ll actual{};
        for (int D = 0; D <= R * C; ++D) {
            actual += AlmostCheckerboards{}.count(R, C, D);
            actual %= M;
        }

        const auto expected = pow_mod(2, R * C, M);
        EXPECT(actual == expected);
    },
};
// clang-format on

int main(int argc, char **argv) { return lest::run(tests, argc, argv); }
