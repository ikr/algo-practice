template <typename T> ostream &operator<<(ostream &os, const vector<T> &xs) {
    os << '[';

    for (auto i = xs.cbegin(); i != xs.cend(); ++i) {
        if (i != xs.cbegin()) os << ' ';
        os << *i;
    }

    os << ']';
    return os;
}

struct Solution final {
    int longestCommonSubsequence(const string &s1, const string &s2) {
        const int sz1 = s1.size();
        const int sz2 = s2.size();
        
        vector<vector<int>> dp(sz1, vector<int>(sz2, 0));
        
        for (int i = 0; i != sz1; ++i) {
            for (int j = 0; j != sz2; ++j) {
                if (s1[i] == s2[j]) {
                    dp[i][j] = 1 + (i > 0 && j > 0 ? dp[i - 1][j - 1] : 0);
                } else {
                    dp[i][j] = max(
                        i > 0 ? dp[i - 1][j] : 0,
                        j > 0 ? dp[i][j - 1] : 0
                    );                    
                }
            }
        }
        
        int ans = 0;
        
        for (int i = 0; i != sz1; ++i) {
            ans = max(ans, dp[i][sz2 - 1]);
        }
        
        for (int j = 0; j != sz2; ++j) {
            ans = max(ans, dp[sz1 - 1][j]);
        }
        
        return ans;
    }
};
