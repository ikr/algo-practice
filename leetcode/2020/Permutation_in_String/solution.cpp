vector<int> gather_counts(const string &s, const int sz) {
    vector<int> ans('z' - 'a' + 1, 0);
    for (int i = 0; i < sz; ++i) {
        ++ans[s[i] - 'a'];
    }
    return ans;
}

struct Solution final {
    bool checkInclusion(const string &p, const string &s) const {
        if (s.size() < p.size()) return false;
        if (p.empty()) return !s.empty();
        
        const auto p_counts = gather_counts(p, p.size());
        auto curr_counts = gather_counts(s, p.size());
        if (p_counts == curr_counts) return true;
        
        for (int i = 1; i + p.size() <= s.size(); ++i) {
            --curr_counts[s[i - 1] - 'a'];
            ++curr_counts[s[i + p.size() - 1] - 'a'];
            if (curr_counts == p_counts) return true;
        }
    
        return false;
    }
};
