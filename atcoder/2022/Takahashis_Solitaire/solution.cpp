#include <bits/stdc++.h>
using namespace std;

using ll = long long;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

map<int, int> gather_freqs(const vector<int> &xs) {
    map<int, int> result;
    for (const auto x : xs) ++result[x];
    return result;
}

vector<int> topo_sort(const vector<vector<int>> &adj) {
    const auto n = sz(adj);
    vector<bool> visited(n, false);
    vector<int> ans;
    ans.reserve(n);

    const auto dfs = [&](const auto self, const int v) -> void {
        visited[v] = true;

        for (int u : adj[v]) {
            if (!visited[u]) {
                self(self, u);
            }
        }
        ans.push_back(v);
    };

    for (int i = 0; i < n; ++i) {
        if (!visited[i]) {
            dfs(dfs, i);
        }
    }

    reverse(ans.begin(), ans.end());
    return ans;
}

ll min_remaining_sum(const vector<int> &A, const int M) {
    const auto fs = gather_freqs(A);

    vector<int> vert;
    vert.reserve(sz(fs));
    for (const auto [a, _] : fs) {
        vert.push_back(a);
    }

    map<int, int> idx;
    for (int i = 0; i < sz(vert); ++i) {
        idx[vert[i]] = i;
    }

    vector<vector<int>> g(sz(vert));
    for (int u = 0; u < sz(vert); ++u) {
        if (idx.count((vert[u] + 1) % M)) {
            const auto v = idx.at((vert[u] + 1) % M);
            g[u].push_back(v);
        }
    }

    const auto topo = topo_sort(g);

    vector<int> sink(sz(topo), -1);
    const auto recur = [&](const auto self, const int u) -> int {
        if (g[u].empty()) {
            sink[u] = u;
            return u;
        }
        if (sink[u] != -1) return sink[u];

        for (const auto v : g[u]) {
            sink[u] = self(self, v);
        }

        return sink[u];
    };

    for (const auto u : topo) {
        sink[u] = recur(recur, u);
    }

    map<int, set<int>> vs_by_sink;
    for (int u = 0; u < sz(sink); ++u) {
        vs_by_sink[sink[u]].insert(u);
    }

    ll S{};
    for (const auto a : A) {
        S += a;
    }

    ll result = LONG_LONG_MAX;
    for (const auto &[_, us] : vs_by_sink) {
        ll cur{};
        for (const auto u : us) {
            cur += vert[u] * fs.at(vert[u]);
        }
        result = min(result, S - cur);
    }
    return result;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int N, M;
    cin >> N >> M;

    vector<int> A(N);
    for (auto &a : A) cin >> a;

    cout << min_remaining_sum(A, M) << '\n';
    return 0;
}
