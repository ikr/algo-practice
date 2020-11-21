#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n, m;
    cin >> n >> m;
    map<pair<int, int>, int> edges;
    multimap<int, int> graph;
    for (int i = 0; i < m; ++i) {
        int u, v, c;
        cin >> u >> v >> c;

        const int a = min(u, v);
        const int b = max(u, v);

        if (edges.count(pair{a, b})) continue;
        edges[pair{a, b}] = c;
        graph.emplace(a, b);
    }

    vector<int> path;
    path.reserve(n);
    set<int> discovered;
    function<void(int)> dfs;

    dfs = [&](const int u) {
        discovered.insert(u);
        path.push_back(u);
        const auto [first, last] = graph.equal_range(u);
        for (auto it = first; it != last; ++it) {
            const auto [u, v] = *it;
            if (discovered.count(v)) continue;
            dfs(v);
        }
    };
    dfs(1);

    return 0;
}
