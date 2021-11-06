using vi = vector<int>;

struct Solution final {
    int lengthOfLIS(const vi &xs) const {
        if (xs.empty()) return 0;
        const int sz = xs.size();

        // dp[i] is minimal value closing the sequence of length i + 1 
        vi dp{xs[0]};

        for (int i = 1; i < sz; ++i) {
            auto it = lower_bound(dp.begin(), dp.end(), xs[i]);
            if (it == dp.end()) dp.push_back(xs[i]);
            else *it = xs[i];
        }

        return dp.size();
    }
};
