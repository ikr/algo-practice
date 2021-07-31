#include <atcoder/dsu>
#include <atcoder/modint>
#include <bits/stdc++.h>
using namespace std;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

using mint = atcoder::modint998244353;
using pii = pair<int, int>;

int k_days_roundtrips(const int k, const int component_size) {
    if (component_size == 1) return 0;
    const mint x{component_size};

    return ((x - 1).pow(k - 1) - (x - 1).pow(k - 2) * (x - 2)).val();
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int n, m, k;
    cin >> n >> m >> k;

    set<pii> cuts;

    for (int i = 0; i < m; ++i) {
        int u, v;
        cin >> u >> v;
        --u;
        --v;
        cuts.emplace(u, v);
        cuts.emplace(v, u);
    }

    atcoder::dsu cs(n);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (i == j || cuts.count(pii{i, j})) continue;
            cs.merge(i, j);
        }
    }

    cout << k_days_roundtrips(k, cs.size(0)) << '\n';
    return 0;
}
