#include <bits/stdc++.h>
using namespace std;
using vs = vector<string>;
using ll = long long;
using vll = vector<ll>;
using vvll = vector<vll>;
static const ll M = 1e9 + 7;

ll solve(const vs &rows) {
    const int sz = rows.size();
    if (!sz) return 0;
    if (rows[0][0] == '*' || rows.back().back() == '*') return 0;

    // number of ways to reach a coord [row r] [column c] modulo M
    vvll dp(sz, vll(sz, 0));
    dp[0][0] = 1;

    for (int c = 1; c < sz; ++c) {
        dp[0][c] = rows[0][c] == '*' ? 0 : dp[0][c - 1];
    }

    for (int r = 1; r < sz; ++r) {
        dp[r][0] = rows[r][0] == '*' ? 0 : dp[r - 1][0];
    }

    for (int r = 1; r < sz; ++r) {
        for (int c = 1; c < sz; ++c) {
            if (rows[r][c] == '*') continue;
            dp[r][c] = (dp[r - 1][c] + dp[r][c - 1]) % M;
        }
    }

    return dp.back().back();
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int sz;
    cin >> sz;
    vs rows(sz, "");
    for (auto &row : rows) cin >> row;

    cout << solve(rows) << '\n';
    return 0;
}
