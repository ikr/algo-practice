#include <atcoder/modint>
#include <bits/stdc++.h>
using namespace std;

using Mint = atcoder::modint1000000007;

struct Alt final {
    Mint capped;
    Mint uncapped;
};

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

int count_ints_with_proper_digits_sum(const string &xs, const int d) {
    // [up to index i in xs] so that [digits sum is j (mod d)]
    vector<vector<Alt>> dp(sz(xs), vector<Alt>(d));

    const int first_x = xs[0] - '0';
    ++dp[0][first_x % d].capped;
    for (int j = first_x - 1; j >= 0; --j) ++dp[0][j % d].uncapped;

    for (int i = 1; i < sz(xs); ++i) {
        const int x0 = xs[i] - '0';

        for (int x = 0; x <= 9; ++x) {
            for (int j = 0; j < d; ++j) {
                if (x < x0) dp[i][(j + x) % d].uncapped += dp[i - 1][j].capped;
                if (x == x0) dp[i][(j + x) % d].capped += dp[i - 1][j].capped;
                dp[i][(j + x) % d].uncapped += dp[i - 1][j].uncapped;
            }
        }
    }

    const auto ans = dp.back()[0].capped + dp.back()[0].uncapped - Mint{1};
    return ans.val();
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    string xs;
    cin >> xs;

    int d;
    cin >> d;

    cout << count_ints_with_proper_digits_sum(xs, d) << '\n';
    return 0;
}
