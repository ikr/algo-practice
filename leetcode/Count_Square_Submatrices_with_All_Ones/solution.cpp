using vi = vector<int>;

struct Solution final {
    int countSquares(const vector<vi> &rows) const {
        const int H = rows.size();
        const int W = rows[0].size();
        
        // number of squares wiht bottom-right at cell [r] [c]
        vector<vi> dp(H, vi(W, 0));
        
        for (int r = 0; r < H; ++r) {
            for (int c = 0; c < W; ++c) {
                if (rows[r][c] == 0) continue;
                
                const int N = r > 0 ? dp[r - 1][c] : 0;
                const int NW = r > 0 && c > 0 ? dp[r - 1][c - 1] : 0;
                const int W = c > 0 ? dp[r][c - 1] : 0;
                
                dp[r][c] = min({N, NW, W}) + 1;
            }
        }
        
        int ans = 0;
        for (const auto &xs : dp) {
            ans += accumulate(xs.cbegin(), xs.cend(), 0);
        }        
        return ans;
    }
};
