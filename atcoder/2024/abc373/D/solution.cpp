#include <atcoder/scc>
#include <bits/stdc++.h>
using namespace std;

using ll = long long;

template <typename T> ostream &operator<<(ostream &os, const vector<T> &xs) {
    for (auto i = xs.cbegin(); i != xs.cend(); ++i) {
        if (i != xs.cbegin()) os << ' ';
        os << *i;
    }
    return os;
}

using pii = pair<int, int>;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int n, m;
    cin >> n >> m;

    atcoder::scc_graph g(n);
    vector<vector<pii>> g0(n);

    for (int i = 0; i < m; ++i) {
        int u, v, w;
        cin >> u >> v >> w;
        --u;
        --v;
        g.add_edge(u, v);
        g0[u].emplace_back(v, w);
    }

    const auto ord = g.scc();

    vector<int> idx(n, -1);
    for (int i = 0; i < sz(ord); ++i) {
        for (const auto u : ord[i]) {
            idx[u] = i;
        }
    }

    vector<vector<pii>> G(sz(ord));
    for (int u = 0; u < n; ++u) {
        for (const auto &[v, w] : g0[u]) {
            if (idx[u] != idx[v]) {
                G[idx[u]].emplace_back(idx[v], w);
            }
        }
    }

    vector<ll> result(n, 0);
    for (const auto u : ord.back()) {
        result[u] = 0;
    }

    for (int i = sz(ord) - 2; i >= 0; --i) {
        const auto v = ord[i][0];

        if (G[idx[v]].empty()) {
            for (const auto vv : ord[i]) {
                result[vv] = 0;
            }
        } else {
            const auto [j, w] = G[idx[v]];
            for (const auto vv : ord[i]) {
                result[vv] = result[u] - w;
            }
        }
    }

    cout << result << '\n';
    return 0;
}
