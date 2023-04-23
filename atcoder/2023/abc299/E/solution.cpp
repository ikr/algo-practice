#include <bits/stdc++.h>
using namespace std;

static constexpr int INF = 1'000'000'000;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

multimap<int, int> vertices_by_distance_from(const vector<vector<int>> &g,
                                             const int u0) {
    const auto n = sz(g);
    vector<int> D(n, INF);
    D[u0] = 0;
    queue<int> q;
    q.push(u0);

    while (!q.empty()) {
        const auto u = q.front();
        q.pop();

        for (const auto v : g[u]) {
            if (D[v] != INF) continue;
            D[v] = D[u] + 1;
            q.push(v);
        }
    }

    multimap<int, int> ans;
    for (int v = 0; v < n; ++v) ans.emplace(D[v], v);
    return ans;
}

string find_coloring(const vector<vector<int>> &g,
                     const vector<int> &req_dist) {
    const auto n = sz(g);
    vector<multimap<int, int>> vbds(n);
    for (auto u0 = 0; u0 < n; ++u0) vbds[u0] = vertices_by_distance_from(g, u0);

    // ??
    return "";
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int N, M;
    cin >> N >> M;

    vector<vector<int>> g(N);
    for (int i = 1; i <= M; ++i) {
        int u, v;
        cin >> u >> v;
        --u;
        --v;

        g[u].push_back(v);
        g[v].push_back(u);
    }

    int K;
    cin >> K;
    vector<int> req_dist(N, -1);
    for (int i = 1; i <= K; ++i) {
        int p, d;
        cin >> p >> d;
        --p;

        req_dist[p] = d;
    }

    const auto ans = find_coloring(g, req_dist);
    if (ans.empty()) {
        cout << "No\n";
    } else {
        cout << "Yes\n" << ans << '\n';
    }
    return 0;
}
