#include <bits/stdc++.h>
using namespace std;
using vi = vector<int>;
static const int M = 1e9 + 7;

int solve(const vi &xs, const int t) {
    const int sz = xs.size();
    
    // number of ways [to get the sum i]
    vi dp(t + 1, 0);
    dp[0] = 1;
    
    for (int i = 1; i <= t; ++i) {
        for (int k = 0; k != sz; ++ k) {
            const int d = xs[k];
            if (i - d >= 0) {
                dp[i] += dp[i - d];
                dp[i] %= M;
            }
        }
    }
    
    return dp.back();
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
