#include <bits/stdc++.h>
using namespace std;
using ll = long long;
static constexpr ll M = 1e9 + 7;

ll solve(const vector<string> &rows) {
    if (rows[0][0] == '#' || rows.back().back() == '#') return 0;

    const int H = rows.size();
    const int W = rows[0].size();

    vector<vector<ll>> dp(H, vector<ll>(W, 0));
    vector<vector<ll>> horz(H, vector<ll>(W, 0));
    vector<vector<ll>> vert(H, vector<ll>(W, 0));
    vector<vector<ll>> diag(H, vector<ll>(W, 0));

    dp[0][0] = 1;
    horz[0][0] = 1;
    vert[0][0] = 1;
    diag[0][0] = 1;

    for (int c = 1; c < W; ++c) {
        if (rows[0][c] == '#') break;
        dp[0][c] = horz[0][c - 1];
        dp[0][c] %= M;

        horz[0][c] = horz[0][c - 1] + dp[0][c];
        horz[0][c] %= M;

        vert[0][c] = dp[0][c];
        diag[0][c] = dp[0][c];
    }

    for (int r = 1; r < H; ++r) {
        if (rows[r][0] == '#') break;
        dp[r][0] = vert[r - 1][0];
        dp[r][0] %= M;

        vert[r][0] = vert[r - 1][0] + dp[r][0];
        vert[r][0] %= M;

        horz[r][0] = dp[r][0];
        diag[r][0] = dp[r][0];
    }

    for (int r = 1; r < H; ++r) {
        for (int c = 1; c < W; ++c) {
            if (rows[r][c] == '#') continue;

            dp[r][c] = horz[r][c - 1];
            dp[r][c] += vert[r - 1][c];
            dp[r][c] += diag[r - 1][c - 1];
            dp[r][c] %= M;

            horz[r][c] = horz[r][c - 1] + dp[r][c];
            horz[r][c] %= M;

            vert[r][c] = vert[r - 1][c] + dp[r][c];
            vert[r][c] %= M;

            diag[r][c] = diag[r - 1][c - 1] + dp[r][c];
            diag[r][c] %= M;
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
