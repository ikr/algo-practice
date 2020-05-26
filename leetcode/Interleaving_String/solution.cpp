struct Solution final {
    bool isInterleave(const string &s1, const string &s2, const string &t) {
        if (s1.size() + s2.size() != t.size()) return false;
        if (s1.empty() || s2.empty()) return s1 + s2 == t;
        
        // answer [up to length i in s1] [up to length j in s2]
        vector<vector<bool>> dp(s1.size() + 1, vector<bool>(s2.size() + 1, false));
        dp[0][0] = true;
        
        for (int i = 1; i <= s1.size(); ++i) dp[i][0] = s1[i - 1] == t[i - 1] && dp[i - 1][0];
        for (int j = 1; j <= s2.size(); ++j) dp[0][j] = s2[j - 1] == t[j - 1] && dp[0][j - 1];
        
        for (int i = 1; i <= s1.size(); ++i) {
            for (int j = 1; j <= s2.size(); ++j) {
                const int k = i + j - 1;
                
                dp[i][j] = (
                    (dp[i - 1][j] && s1[i - 1] == t[k]) ||
                    (dp[i][j - 1] && s2[j - 1] == t[k])
                );
            }
        }
        
        return dp.back().back();
    }
};
