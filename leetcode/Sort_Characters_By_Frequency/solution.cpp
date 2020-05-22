struct Solution final {
    string frequencySort(string s) const {
        vector<int> counts(CHAR_MAX + 1, 0);
        for (const char c : s) ++counts[c];
        
        sort(s.begin(), s.end(), [&counts](const char lhs, const char rhs) {
            if (counts[lhs] == counts[rhs]) return lhs < rhs;
            return counts[lhs] > counts[rhs];
        });
        
        return s;
    }
};
