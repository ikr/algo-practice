struct Solution final {
    bool wordBreak(const string &s, const vector<string> &dict_v) const {
        if (s.empty()) return false;
        const unordered_set<string> dict(dict_v.cbegin(), dict_v.cend());
        const int sz = s.size();        

        // is compound ending at [i]
        vector<bool> dp(sz, false);
        
        for (int i = 0; i != sz; ++i) {
            for (int j = i - 1; j >= -1; --j) {
                if (j == -1) {
                    dp[i] = dict.count(s.substr(0, i + 1));                
                } else {
                    if (dp[j] && dict.count(s.substr(j + 1, i - j))) {
                        dp[i] = true;
                        break;
                    }
                }
            }
        }

        return dp.back();
    }
};
