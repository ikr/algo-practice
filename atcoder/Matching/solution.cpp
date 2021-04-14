#include <bits/stdc++.h>
using namespace std;

using vi = vector<int>;
using vvi = vector<vi>;
static constexpr int M = 1e9 + 7;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

int num_ways(const vvi &grid) {
    const int n = sz(grid);
    vi dp(1 << n, 0);
    dp[0] = 1;

    for (int bits = 1; bits < (1 << n); ++bits) {
        const int paired = __builtin_popcount(bits);

        for (int i = 0; i < n; ++i) {
            if (grid[paired - 1][i] == 1 && ((1 << i) & bits)) {
                dp[bits] += dp[~(1 << i) & bits];
                dp[bits] %= M;
            }
        }
    }

    return dp.back();
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int n;
    cin >> n;

    vvi grid(n, vi(n));
    for (auto &row : grid) {
        for (auto &cell : row) cin >> cell;
    }

    cout << num_ways(grid) << '\n';
    return 0;
}
