#include <bits/stdc++.h>
using namespace std;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

unordered_map<int, int> distances_from(const vector<vector<int>> &g,
                                       const int src) {
    unordered_map<int, int> ans;
    ans[src] = 0;

    queue<int> q;
    q.push(src);

    while (!q.empty()) {
        const auto u = q.front();
        q.pop();

        for (const auto v : g[u]) {
            if (ans.count(v)) continue;
            ans[v] = ans[u] + 1;
            q.push(v);
        }
    }

    return ans;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int n1, n2, m;
    cin >> n1 >> n2 >> m;

    vector<vector<int>> g(n1 + n2);
    for (int i = 0; i < m; ++i) {
        int u, v;
        cin >> u >> v;
        --u;
        --v;

        g[u].push_back(v);
        g[v].push_back(u);
    }

    const auto D1 = distances_from(g, 0);
    int hi1 = 0;

    for (const auto &[u, d] : D1) {
        if (d > hi1) hi1 = d;
    }

    const auto D2 = distances_from(g, n1 + n2 - 1);
    int hi2 = 0;

    for (const auto &[u, d] : D2) {
        if (d > hi2) hi2 = d;
    }

    cout << (hi1 + hi2 + 1) << '\n';
    return 0;
}
