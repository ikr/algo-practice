class Solution {
public:
    bool canJump(const vector<int> &xs) {
        const int sz = xs.size();
        if (!sz) return false;
        
        vector<bool> dp(sz, false);
        dp[0] = true;
        
        for (int i = 0; i != sz; ++i) {
            if (!dp[i]) continue;
            
            for (int j = 1; i + j < sz && j <= xs[i]; ++j) {
                dp[i + j] = true;
            }
        }
        
        return dp.back();
    }
};
