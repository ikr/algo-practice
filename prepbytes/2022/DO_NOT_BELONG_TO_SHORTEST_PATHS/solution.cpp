#include <bits/stdc++.h>
using namespace std;

using pii = pair<int, int>;

static constexpr int INF = 1e9;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

pii canonical(const pii xy) {
    const auto x = xy.first;
    const auto y = xy.second;
    assert(x != y);
    return {min(x, y), max(x, y)};
}

int unused_edges_count(const vector<vector<pii>> &g) {
    const auto n = sz(g);
    vector<vector<int>> D(n, vector<int>(n, INF));
    for (int u = 0; u < n; ++u) D[u][u] = 0;

    set<pii> used;
    for (int u = 0; u < n; ++u) {
        for (const auto &vw : g[u]) {
            const auto v = vw.first;
            const auto w = vw.second;
            D[u][v] = w;
            D[v][u] = w;
            used.insert(canonical({u, v}));
        }
    }

    for (int k = 0; k < n; ++k) {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (D[i][k] + D[k][j] < D[i][j]) {
                    D[i][j] = D[i][k] + D[k][j];
                    used.erase(canonical({i, j}));
                    used.insert(canonical({i, k}));
                    used.insert(canonical({k, j}));
                }
            }
        }
    }

    set<pii> unused;

    for (int u = 0; u < n; ++u) {
        for (const auto &vw : g[u]) {
            const auto v = vw.first;
            if (used.count(canonical({u, v}))) continue;
            unused.insert(canonical({u, v}));
        }
    }

    return sz(unused);
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int N, M;
    cin >> N >> M;

    vector<vector<pii>> g(N);

    for (int i = 1; i <= M; ++i) {
        int u, v, w;
        cin >> u >> v >> w;
        --u;
        --v;

        g[u].emplace_back(v, w);
        g[v].emplace_back(u, w);
    }

    cout << unused_edges_count(g) << '\n';
    return 0;
}
