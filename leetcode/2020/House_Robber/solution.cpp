struct Solution final {
    int rob(const vector<int> &xs) {
        const int sz = xs.size();
        if (!sz) return 0;
        
        vector<int> dp(sz, 0);
        dp[0] = xs[0];
        if (sz > 1) dp[1] = max(dp[0], xs[1]);

        for (int i = 2; i < sz; ++i) {
            dp[i] = max(dp[i - 1], dp[i - 2] + xs[i]);
        }
        
        return dp[sz - 1];
    }
};
