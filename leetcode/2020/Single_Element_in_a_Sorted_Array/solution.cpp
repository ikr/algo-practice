struct Solution final {
    int singleNonDuplicate(const vector<int> &xs) const {
        int ans = 0;
        for (const int x : xs) ans ^= x;
        return ans;
    }
};
