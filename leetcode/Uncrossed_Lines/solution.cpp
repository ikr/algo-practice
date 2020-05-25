using vi = vector<int>;
using vvi = vector<vi>;

struct Solution final {
    int maxUncrossedLines(const vi &xs, const vi &ys) const {
        if (xs.empty() || ys.empty()) return 0;
        const int szx = xs.size();
        const int szy = ys.size();
        
        // answer [up to index i in xs] [up to index j in ys]
        vvi dp(szx, vi(szy, 0));
        
        for (int i = 0; i < szx; ++i) {
            for (int j = 0; j < szy; ++j) {
                if (xs[i] == ys[j]) {
                    dp[i][j] = 1 + (i > 0 && j > 0 ? dp[i - 1][j - 1] : 0); 
                } else {
                    dp[i][j] = max(i > 0 ? dp[i - 1][j] : 0, j > 0 ? dp[i][j - 1] : 0);
                }
            }
        }
        
        return dp.back().back();
    }
};
