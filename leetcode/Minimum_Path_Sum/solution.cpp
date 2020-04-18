class Solution {
public:
    int minPathSum(const vector<vector<int>> &rows) {
        const int H = rows.size();
        if (!H) return 0;
        
        const int W = rows.front().size();
        if (!W) return 0;
        
        vector<vector<int>> dp(H, vector<int>(W, INT_MAX));
        dp[0][0] = rows[0][0];
        
        for (int r = 1; r != H; ++r) dp[r][0] = dp[r - 1][0] + rows[r][0];
        for (int c = 1; c != W; ++c) dp[0][c] = dp[0][c - 1] + rows[0][c];                
        
        for (int r = 1; r != H; ++r) {
            for (int c = 1; c != W; ++c) {                
                dp[r][c] = min(dp[r - 1][c], dp[r][c - 1]) + rows[r][c];
            }
        }
        
        return dp[H - 1][W - 1];
    }
};
