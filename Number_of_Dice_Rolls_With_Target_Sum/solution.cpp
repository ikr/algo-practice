using ll = long long;
using vll = vector<ll>;
static const ll M = 1e9 + 7;

struct Solution final {
    int numRollsToTarget(const int d, const int f, const int target) const {
        // ways [using i dice] [sum j to get]        
        vector<vll> dp(d + 1, vll(target + 1, 0LL));
        
        for (int j = 1; j <= target && j <= f; ++j) {
            dp[1][j] = 1;
        }
        
        for (int i = 2; i <= d; ++i) {
            for (int j = 1; j <= target; ++j) {
                dp[i][j] = dp[i - 1][j];
                
                for (int k = 1; k <= f && j - k > 0; ++k) {
                    dp[i][j] = (dp[i][j] + dp[i - 1][j - k]) % M;
                }
            }
        }
        
        return dp.back().back();
    }
};
