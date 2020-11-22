#include <bits/stdc++.h>
using namespace std;

template <typename T> constexpr double doof(const T x) {
    return static_cast<double>(x);
}

static constexpr double INF = 1e16;

double recur(vector<vector<vector<double>>> &dp, const int a, const int b,
             const int c) {
    if (dp[a][b][c] == INF) {
        dp[a][b][c] = (doof(a - 1) * (recur(dp, a - 1, b, c) + 1) +
                       doof(b - 1) * (recur(dp, a, b - 1, c) + 1) +
                       doof(c - 1) * (recur(dp, a, b, c - 1) + 1)) /
                      doof(a + b + c - 1);
    }

    return dp[a][b][c];
}

double solve(const int a0, const int b0, const int c0) {
    vector<vector<vector<double>>> dp(
        101, vector<vector<double>>(101, vector<double>(101, INF)));

    dp[a0][b0][c0] = 0;

    if (a0) recur(dp, 100, b0, c0);
    if (b0) recur(dp, a0, 100, c0);
    if (c0) recur(dp, a0, b0, 100);

    double ans = INF;

    for (int i = 0; i <= 100; ++i) {
        for (int j = 0; j <= 100; ++j) {
            ans = min(ans, dp[100][i][j]);
            ans = min(ans, dp[i][100][j]);
            ans = min(ans, dp[i][j][100]);
        }
    }

    return ans;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout << setprecision(7) << fixed;

    int a0, b0, c0;
    cin >> a0 >> b0 >> c0;
    cout << solve(a0, b0, c0) << '\n';

    return 0;
}
