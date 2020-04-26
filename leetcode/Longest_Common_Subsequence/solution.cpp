vector<string> adjacent(string s) {
    vector<string> ans;
    
    for (auto i = 0U; i < s.size(); ++i) {
        const char c = s[i];
        s.erase(i, 1);
        ans.push_back(s);
        s.insert(i, 1, c);
    }
        
    return ans;
}

string pop(queue<string> &q) {
    assert(!q.empty());
    string ans = q.front();
    q.pop();
    return ans;
}

struct Solution final {
    int longestCommonSubsequence(string s1, string s2) {
        if (s1.empty() || s2.empty()) return 0;
        if (s1 == s2) return s1.size();
        
        unordered_set<string> discovered1{s1};
        queue<string> q1;
        q1.push(s1);
        
        unordered_set<string> discovered2{s2};
        queue<string> q2;
        q2.push(s2);
        
        while(!q1.empty() || !q2.empty()) {
            if (!q1.empty()) {
                auto u1 = pop(q1);
                
                for (const auto v1 : adjacent(u1)) {
                    if (discovered1.count(v1)) continue;
                    if (discovered2.count(v1)) return v1.size();
                    discovered1.insert(v1);
                    q1.push(v1);
                }
            }

            if (!q2.empty()) {
                auto u2 = pop(q2);
                
                for (const auto v2 : adjacent(u2)) {
                    if (discovered2.count(v2)) continue;
                    if (discovered1.count(v2)) return v2.size();
                    discovered2.insert(v2);
                    q2.push(v2);
                }
            }
        }
        
        return 0;
    }
};
