using umm = unordered_multimap<int, int>;
using vvi = vector<vector<int>>;

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

template <typename T> ostream &operator<<(ostream &os, const vector<T> &xs) {
    os << '[';
    for (auto i = xs.cbegin(); i != xs.cend(); ++i) {
        if (i != xs.cbegin()) os << ' ';
        os << *i;
    }
    os << ']';
    return os;
}

template <typename T> ostream &operator<<(ostream &os, const vector<vector<T>> &xss) {
    for (const auto xs : xss) os << xs << '\n';
    return os;
}

static const vector<tuple<int, vvi, bool>> testCases {
    {1, {}, true},
    {2, {{0,1}}, true},
    {2, {{1,0},{0,1}}, false},
    {3, {{1,0},{1,2},{0,1}}, false},
    {3, {{0,1},{1,2},{2,0}}, false},
    {3, {{0,1},{0,2},{1,2}}, true},
    {4, {{1,0},{1,3},{2,0},{3,2}}, true},
    {4, {{2,0},{1,0},{3,1},{3,2},{1,3}}, false},
    {7, {{1,2},{2,3},{4,1},{4,5},{5,2},{5,3},{3,6}}, true},
    {7, {{1,2},{2,3},{3,4},{4,5},{5,6},{6,4}}, false}
};

int main() {
    bool ok = true;
    
    for (const auto [sz, prerequisites, expected] : testCases) {
        const auto actual = Solution{}.canFinish(sz, prerequisites);
        cout << (actual == expected ? '.' : 'F');
        if (actual != expected) {
            cout << '\n' << prerequisites << '\n';
            break;
        }
    }
    
    cout << '\n' << (ok ? "\\o/" : "/o\\") << '\n';
    return 0;
}
