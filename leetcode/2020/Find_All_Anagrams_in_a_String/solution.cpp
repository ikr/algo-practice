vector<int> gather_counts(const string &s, const int sz) {
    vector<int> ans('z' - 'a' + 1, 0);
    for (int i = 0; i < sz; ++i) {
        ++ans[s[i] - 'a'];
    }
    return ans;
}

struct Solution final {
    vector<int> findAnagrams(const string &s, string p) const{
        if (s.size() < p.size()) return {};
        const auto p_counts = gather_counts(p, p.size());
        auto curr_counts = gather_counts(s, p.size());
        
        vector<int> ans;
        if (p_counts == curr_counts) ans.push_back(0);
        
        for (int i = 1; i + p.size() <= s.size(); ++i) {
            --curr_counts[s[i - 1] - 'a'];
            ++curr_counts[s[i + p.size() - 1] - 'a'];
            if (curr_counts == p_counts) ans.push_back(i);
        }
        
        return ans;
    }
};
