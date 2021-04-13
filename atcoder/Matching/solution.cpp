#include <atcoder/modint>
#include <bits/stdc++.h>
using namespace std;

using vi = vector<int>;
using vvi = vector<vi>;
using Mint = atcoder::modint1000000007;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

int num_ways(const vvi &grid) {
    const int n = sz(grid);

    vvi dp(n, vi(1 << n, 0));

    for (int co = 0; co < n; ++co) {
        if (grid[0][co] == 1) dp[0][1 << co] = 1;
    }

    for (int ro = 1; ro < n; ++ro) {
        for (int bits = 1; bits < (1 << n); ++bits) {
        }
    }

    return dp.back().back();
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
