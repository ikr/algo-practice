#include <bits/stdc++.h>
using namespace std;
using vi = vector<int>;
using vvi = vector<vi>;
static const int M = 1e9 + 7;

int solve(const vi &xs, const int t) {
    const int sz = xs.size();
    
    // number of ways [using i first denominations] [to get the sum i]
    vvi dp(sz + 1, vi(t + 1, 0));
    for (int i = 0; i <= sz; ++i) dp[i][0] = 1;
    
    for (int i = 1; i <= sz; ++i) {
        for (int j = 1; j <= t; ++j) {
            const int d = xs[i - 1]; 
            dp[i][j] = dp[i - 1][j];
            
            if (j - d >= 0) {
                dp[i][j] += dp[i][j - d];
                dp[i][j] %= M;
            }
        }
    }
    
    return dp.back().back();
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    
    int sz, t;
    cin >> sz >> t;
    vi xs(sz);
    for (auto &x : xs) cin >> x;
    
    cout << solve(xs, t) << '\n';
    return 0;
}
