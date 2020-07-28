#include <bits/stdc++.h>
using namespace std;
using vi = vector<int>;
using vvi = vector<vi>;
static constexpr int INF = 1e9 + 10;

int min_cuts(const int a, const int b) {
    const int sz = max(a, b);
    vvi dp(sz + 1, vi(sz + 1, INF));
    
    for (int i = 1; i <= sz; ++i) {
        for (int j = 1; j <= i; ++j) {
            if (i == j) {
                dp[i][j] = 0;
                continue;
            }
            
            for (int ik = 1; ik < i; ++ik) {
                dp[i][j] = min(dp[i][j], dp[ik][j] + dp[i - ik][j] + 1);
            }
            
            for (int jk = 1; jk < j; ++jk) {
                dp[i][j] = min(dp[i][j], dp[i][jk] + dp[i][j - jk] + 1); 
            }
            
            dp[j][i] = dp[i][j];
        }
    }
    
    return dp[a][b];
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int a, b;
    cin >> a >> b;
    cout << min_cuts(a, b) << '\n';
    return 0;
}
