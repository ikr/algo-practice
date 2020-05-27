template <typename T> constexpr int intof(const T x) { return static_cast<int>(x); }
using ll = long long;

struct Solution final {
    int numDistinct(const string &s, const string &t) const {
        if (t.empty()) return 1;
        const int ssz = s.size();
        const int tsz = t.size();
        if (ssz < tsz) return 0;
        
        // answer for prefix strings [in s up to size i] [in t up to size j]
        vector<vector<ll>> dp(ssz + 1, vector<ll>(tsz + 1, 0));
        for (int i = 0; i <= ssz; ++i) dp[i][0] = 1;

        for (int i = 1; i <= ssz; ++i) {
            for (int j = 1; j <= tsz; ++j) {
                if (s[i - 1] == t[j - 1]) {
                    dp[i][j] = dp[i - 1][j] + dp[i - 1][j - 1]; 
                } else {
                    dp[i][j] = dp[i - 1][j];
                }
            }
        }

        return intof(dp.back().back());
    }
};
