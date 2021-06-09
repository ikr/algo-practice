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

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

vvll combinations(const int n, const int k) {
    assert(k <= n);
    vvll ans(n + 1, vll(k + 1, 1));

    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= min(i, k); ++j) {
            ans[i][j] = i == j ? 1 : ans[i - 1][j - 1] + ans[i - 1][j];
        }
    }

    return ans;
}

struct Flagpole final {
    ll build(vi xs, const ll lo, const ll hi) const {
        const auto n_choose_k = combinations(40, 40);
        sort(begin(xs), end(xs));
        return 42;
    }
};

// clang-format off
const lest::test tests[] = {
    CASE("Example 0") {
        const auto actual = Flagpole{}.build({10, 10, 10, 10, 10}, 9, 49);
        const auto expected = 30LL;
        EXPECT(actual == expected);
    },
    CASE("Example 1") {
        const auto actual = Flagpole{}.build({10, 10, 10, 10, 10}, 30, 39);
        const auto expected = 0LL;
        EXPECT(actual == expected);
    },
    CASE("Example 2") {
        const auto actual = Flagpole{}.build({1, 2, 4, 8, 16, 32, 64, 128}, 47, 100);
        const auto expected = 53LL;
        EXPECT(actual == expected);
    },
    CASE("Example 3") {
        const auto actual = Flagpole{}.build({50, 10, 40, 30, 20}, 45, 63);
        const auto expected = 6LL;
        EXPECT(actual == expected);
    },
};
// clang-format on

int main(int argc, char **argv) { return lest::run(tests, argc, argv); }
