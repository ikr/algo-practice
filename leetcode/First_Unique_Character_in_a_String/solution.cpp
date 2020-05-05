struct Solution final {
    int firstUniqChar(const string &s) const {
        unordered_map<char, int> counts;
        for (const char c : s) {
            ++counts[c];
        }
        
        const int sz = s.size();
        
        for (int i = 0; i != sz; ++i) {
            if (counts[s[i]] == 1) return i;
        }
        
        return -1;
    }
};
