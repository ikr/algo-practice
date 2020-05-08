#include <bits/stdc++.h>

using namespace std;
using ui = unsigned int;
using ll = long long;
using vll = vector<ll>;
static const ll M = 1e9 + 7;

ll solve(const vector<string> &rows) {
    const int H = rows.size();
    const int W = rows.front().size();
    
    // count of paths to reach [row r] [column c]
    vector<vll> dp(H, vll(W, 0));
    dp[0][0] = 1;
    for (int c = 1; c < W && rows[0][c] != '#'; ++c) dp[0][c] = 1;
    for (int r = 1; r < H && rows[r][0] != '#'; ++r) dp[r][0] = 1;
    
    for (int r = 1; r < H; ++r) {
        for (int c = 1; c < W; ++c) {
            if (rows[r][c] == '#') continue;
            dp[r][c] = (dp[r][c] + dp[r - 1][c] + dp[r][c - 1]) % M;
        }
    }
    
    return dp.back().back();
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    ui H, W;
    cin >> H >> W;
    vector<string> rows(H, "");
    for (auto &row : rows) {
        cin >> row;
        assert(row.size() == W);
    }
    
    cout << solve(rows) << endl;
    
    return 0;
}
