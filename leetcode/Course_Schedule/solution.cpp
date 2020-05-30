using umm = unordered_multimap<int, int>;
using vvi = vector<vector<int>>;
enum class State {PENDING, DISCOVERED, PROCESSED};

bool is_cyclic(const int sz, const umm &follow) {
    unordered_map<int, State> work;
    
    for (int x = 0; x < sz; ++x) {
        if (work[x] == State::PROCESSED) continue;
        
        stack<int> frontier;
        stack<int> origin;
        frontier.push(x);
        work[x] = State::DISCOVERED;
        
        while (!frontier.empty()) {
            const auto u = frontier.top();
            
            if (!origin.empty() && origin.top() == u) {
                frontier.pop();
                origin.pop();
                work[u] = State::PROCESSED;
                continue;
            }
            
            origin.push(u);

            const auto [first, last] = follow.equal_range(u);
            for (auto it = first; it != last; ++it) {
                const int v = it->second;
                if (work[v] == State::PROCESSED) continue;
                if (work[v] == State::DISCOVERED) return true;
                work[v] = State::DISCOVERED;
                frontier.push(v);
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
    {7, {{1,2},{2,3},{3,4},{4,5},{5,6},{6,4}}, false},
    {12, {{5,11},{11,2},{11,9},{11,10},{7,11},{7,8},{8,9},{3,8},{3,10}}, true},
    {12, {{5,11},{11,2},{11,9},{11,10},{7,11},{7,8},{8,9},{3,8},{3,10},{10,5}}, false}
};

int main() {
    bool ok = true;
    
    for (const auto [sz, prerequisites, expected] : testCases) {
        const auto actual = Solution{}.canFinish(sz, prerequisites);
        cout << (actual == expected ? '.' : 'F');
        if (actual != expected) {
            ok = false;
            cout << '\n' << prerequisites;
            break;
        }
    }
    
    cout << (ok ? "\n\\o/" : "/o\\") << '\n';
    return 0;
}
