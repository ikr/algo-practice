#include <atcoder/dsu>
#include <atcoder/modint>
#include <bits/stdc++.h>

using namespace std;

using vi = vector<int>;
using vvi = vector<vi>;
using pii = pair<int, int>;
using mint = atcoder::modint998244353;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

bool is_ok(const vvi &g, const vi &us) {
    set<pii> edges;

    for (const auto u : us) {
        for (const auto v : g[u]) {
            edges.emplace(min(u, v), max(u, v));
        }
    }

    return sz(us) == sz(edges);
}

mint num_ways(const vvi &g, const vvi &cs) {
    if (all_of(cbegin(cs), cend(cs),
               [&g](const vi &us) { return is_ok(g, us); })) {
        return mint{2}.pow(sz(cs));
    }

    return 0;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int n, m;
    cin >> n >> m;

    vvi g(n);
    atcoder::dsu cs(n);

    for (int i = 0; i < m; ++i) {
        int u, v;
        cin >> u >> v;
        --u;
        --v;

        g[u].push_back(v);
        g[v].push_back(u);

        cs.merge(u, v);
    }

    cout << num_ways(g, cs.groups()).val() << '\n';
    return 0;
}
