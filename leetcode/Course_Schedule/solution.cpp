using umm = unordered_multimap<int, int>;

bool is_cyclic(const int sz, const umm &follow) {
    for (int src = 0; src < sz; ++src) {
        unordered_set<int> discovered;
        stack<int> st;
        st.push(src);
        discovered.insert(src);
        
        while (!st.empty()) {
            const auto u = st.top();
            st.pop();
            
            const auto [first, last] = follow.equal_range(u);
            for (auto it = first; it != last; ++it) {
                if (it->second == src) return true;
                if (discovered.count(it->second)) continue;
                discovered.insert(it->second);
                st.push(it->second);
            }
        }
    }
    
    return false;
}

struct Solution final {
    bool canFinish(const int sz, const vector<vector<int>> &prerequisites) const {
        umm follow;
        for (const auto &p : prerequisites) follow.emplace(p[1], p[0]); 
        return !is_cyclic(sz, follow);
    }
};
