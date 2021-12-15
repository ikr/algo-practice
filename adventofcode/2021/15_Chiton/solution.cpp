#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vi = vector<int>;
using vvi = vector<vi>;
using pii = pair<int, int>;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}
template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

static constexpr int INF = 1e9;

int min_total_risk(const vvi &grid) {
    const int H = sz(grid);
    const int W = sz(grid[0]);

    vvi dp(H, vi(W, INF));
    dp[0][0] = 0;

    for (int co = 1; co < W; ++co) {
        dp[0][co] = dp[0][co - 1] + grid[0][co];
    }

    for (int ro = 1; ro < H; ++ro) {
        dp[ro][0] = dp[ro - 1][0] + grid[ro][0];
    }

    for (int ro = 1; ro < H; ro++) {
        for (int co = 1; co < W; ++co) {
            dp[ro][co] = min(dp[ro - 1][co], dp[ro][co - 1]) + grid[ro][co];
        }
    }

    return dp.back().back();
}

int main() {
    vector<string> lines;

    for (string line; getline(cin, line);) {
        lines.push_back(line);
    }

    vvi grid(sz(lines), vi(sz(lines[0]), -1));
    for (int ro = 0; ro < sz(lines); ++ro) {
        for (int co = 0; co < sz(lines[0]); ++co) {
            grid[ro][co] = inof(lines[ro][co]) - inof('0');
        }
    }

    cout << min_total_risk(grid) << '\n';
    return 0;
}
