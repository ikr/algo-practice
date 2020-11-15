#include <bits/stdc++.h>
using namespace std;
using ll = long long;
static constexpr ll M = 1e9 + 7;

ll solve(const vector<string> &rows) {
    const int H = rows.size();
    const int W = rows[0].size();

    vector<vector<ll>> dp(H, vector<ll>(W, 0));
    dp[0][0] = rows[0][0] == '.' ? 1 : 0;

    for (int c = 1; c < W; ++c) {
        dp[0][c] = rows[0][c] == '.' ? dp[0][c - 1] : 0;
    }

    for (int r = 1; r < H; ++r) {
        dp[r][0] = rows[r][0] == '.' ? dp[r - 1][0] : 0;
    }

    for (int r = 1; r < H; ++r) {
        for (int c = 1; c < W; ++c) {
            if (rows[r][c] == '#') continue;

            dp[r][c] = dp[r - 1][c - 1] + dp[r - 1][c] + dp[r][c - 1];
            dp[r][c] %= M;
        }
    }

    return dp.back().back();
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int H, W;
    cin >> H >> W;
    vector<string> rows(H, string(W, ' '));

    for (auto &row : rows) {
        cin >> row;
    }

    cout << solve(rows) << '\n';
    return 0;
}
