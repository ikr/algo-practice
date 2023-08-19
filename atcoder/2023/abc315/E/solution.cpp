#include <bits/stdc++.h>
using namespace std;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

template <typename T> ostream &operator<<(ostream &os, const vector<T> &xs) {
    for (auto i = xs.cbegin(); i != xs.cend(); ++i) {
        if (i != xs.cbegin()) os << ' ';
        os << *i;
    }
    return os;
}

template <typename T>
ostream &operator<<(ostream &os, const unordered_set<T> &xs) {
    os << '{';
    for (auto i = xs.cbegin(); i != xs.cend(); ++i) {
        if (i != xs.cbegin()) os << ' ';
        os << *i;
    }
    os << '}';
    return os;
}

unordered_set<int> interesting_vertices(const vector<vector<int>> &g) {
    unordered_set<int> ans;
    const auto dfs = [&](const auto &self, const auto u) -> void {
        ans.insert(u);
        for (const auto v : g[u]) {
            if (ans.count(v)) continue;
            self(self, v);
        }
    };
    dfs(dfs, 0);
    return ans;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int N;
    cin >> N;

    vector<vector<int>> g(N);
    vector<vector<int>> g_(N);
    vector<int> deg(N, 0);

    for (int u = 0; u < N; ++u) {
        int m;
        cin >> m;

        for (int j = 0; j < m; ++j) {
            int v;
            cin >> v;
            --v;
            g[u].push_back(v);
            ++deg[u];
            g_[v].push_back(u);
        }
    }

    const auto ivs = interesting_vertices(g);
    queue<int> q;

    for (int u = 0; u < N; ++u) {
        if (!deg[u] && ivs.contains(u)) {
            q.push(u);
        }
    }

    vector<int> ans;
    ans.reserve(sz(ivs));

    while (!q.empty()) {
        const auto u = q.front();
        q.pop();
        ans.push_back(u);

        for (const auto v : g_[u]) {
            --deg[v];
            if (!deg[v]) q.push(v);
        }
    }

    ans.pop_back();
    for (auto &x : ans) ++x;
    cout << ans << '\n';
    return 0;
}
