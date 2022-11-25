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

vector<int> vconcat(vector<int> xs, const vector<int> &ys) {
    xs.insert(xs.cend(), ys.cbegin(), ys.cend());
    return xs;
}

int unused_edges_count(const int M, const vector<vector<pii>> &g) {
    const auto n = sz(g);

    vector<vector<int>> D(n, vector<int>(n, INF));
    for (int u = 0; u < n; ++u) D[u][u] = 0;

    vector<vector<int>> P(n, vector<int>(n, -1));

    for (int u = 0; u < n; ++u) {
        for (const auto &vw : g[u]) {
            const auto v = vw.first;
            const auto w = vw.second;
            D[u][v] = w;
            D[v][u] = w;
        }
    }

    for (int k = 0; k < n; ++k) {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (D[i][k] + D[k][j] < D[i][j]) {
                    D[i][j] = D[i][k] + D[k][j];
                    P[i][j] = k;
                }
            }
        }
    }

    const auto path_between = [&](const auto self, const int src,
                                  const int dst) -> vector<int> {
        assert(src != dst);
        if (P[src][dst] == -1) return {src, dst};
        auto result =
            vconcat(self(self, src, P[src][dst]), self(self, P[src][dst], dst));
        result.erase(unique(result.begin(), result.end()), end(result));
        return result;
    };

    set<pii> used;

    for (int u = 0; u < n - 1; ++u) {
        for (int v = u + 1; v < n; ++v) {
            const auto path = path_between(path_between, u, v);
            for (int i = 1; i < sz(path); ++i) {
                used.insert(canonical({path[i - 1], path[i]}));
            }
        }
    }

    return M - sz(used);
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

    cout << unused_edges_count(M, g) << '\n';
    return 0;
}
