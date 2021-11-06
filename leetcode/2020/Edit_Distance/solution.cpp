struct Solution final {
    int minDistance(const string &s1, const string &s2) const {
        // answer for [prefix of length i in s1] [prefix of length j in s2]
        vector<vector<int>> dp(s1.size() + 1, vector<int>(s2.size() + 1, 0));
        
        iota(dp[0].begin(), dp[0].end(), 0);
        for (auto i = 1U; i <= s1.size(); ++i) dp[i][0] = i;
        
        for (auto i = 1U; i <= s1.size(); ++i) {
            for (auto j = 1U; j <= s2.size(); ++j) {
                if (s1[i - 1] == s2[j - 1]) {
                    dp[i][j] = dp[i - 1][j - 1];
                } else {
                    dp[i][j] = min({dp[i - 1][j], dp[i][j - 1], dp[i - 1][j - 1]}) + 1;
                }
            }
        }
        
        return dp.back().back();
    }
};
