void shift(string &s, const char leaving, const char entering) {
    auto it = lower_bound(s.cbegin(), s.cend(), leaving);
    s.erase(it);
    
    it = upper_bound(s.cbegin(), s.cend(), entering);
    s.insert(it, entering);
}

struct Solution final {
    vector<int> findAnagrams(const string &s, string p) const{
        if (s.size() < p.size()) return {};
        sort(p.begin(), p.end());
        string curr(s.cbegin(), s.cbegin() + p.size());
        sort(curr.begin(), curr.end());
        
        vector<int> ans;
        if (curr == p) ans.push_back(0);
        
        for (int i = 1; i + p.size() <= s.size(); ++i) {
            shift(curr, s[i - 1], s[i + p.size() - 1]);
            if (curr == p) ans.push_back(i);
        }
        
        return ans;
    }
};
