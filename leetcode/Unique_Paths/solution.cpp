using vi = vector<int>;
using vvi = vector<vi>;

struct Solution final {
    int uniquePaths(const int m, const int n) const {
        if (!n || !m) return 0;
        
        // number of ways to reach a coord [row r] [column c]
        vvi dp(m, vi(n, 0));
        dp[0][0] = 1;
        for (int c = 1; c < n; ++c) dp[0][c] = 1;
        for (int r = 1; r < m; ++r) dp[r][0] = 1;

        for (int r = 1; r < m; ++r) {
            for (int c = 1; c < n; ++c) {
                dp[r][c] = (dp[r - 1][c] + dp[r][c - 1]);
            }
        }
        
        return dp.back().back();
    }
};
