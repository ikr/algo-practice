#include <bits/stdc++.h>
using namespace std;
using vi = vector<int>;
using vvi = vector<vi>;

int solve(const int t, const vi &xs) {
    const int sz = xs.size();
    
    // min coins count [using up to i first denominations of xs] [to gather sum j]
    vvi dp(sz + 1, vi(t + 1, INT_MAX));
    for (int i = 0; i <= sz; ++i) dp[i][0] = 0;

    for (int i = 1; i <= sz; ++i) {
        for (int j = 1; j <= t; ++j) {
            const int d = xs[i - 1];
            
            dp[i][j] = min(
                dp[i - 1][j], 
                (j - d >= 0 && dp[i][j - d] != INT_MAX) ? dp[i][j - d] + 1 : INT_MAX
            );
        }
    }
    
    return dp.back().back() == INT_MAX ? -1 : dp.back().back();
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n, t;
    cin >> n >> t;
    vi xs(n, 0);
    for (int &x : xs) cin >> x;
    
    cout << solve(t, xs) << '\n';
    return 0;
}
