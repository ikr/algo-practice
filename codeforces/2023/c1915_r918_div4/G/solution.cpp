#include <bits/stdc++.h>
using namespace std;

using ll = long long;

static constexpr ll Inf = 1e16L;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int T;
    cin >> T;

    while (T--) {
        int n, m;
        cin >> n >> m;

        vector<vector<pair<int, int>>> proto_g(n);
        for (int i = 1; i <= m; ++i) {
            int u, v, w;
            cin >> u >> v >> w;
            --u;
            --v;
            proto_g[u].emplace_back(v, w);
            proto_g[v].emplace_back(u, w);
        }

        vector<int> S(n);
        for (auto &s : S) cin >> s;

        vector<vector<pair<int, int>>> g(n);

        for (int u = 0; u < n; ++u) {
            for (const auto &[v, w] : proto_g[u]) {
                g[u].emplace_back(v, w * S[u]);
            }
        }

        vector<ll> D(n, Inf);
        D[0] = 0;

        set<pair<ll, int>> q;
        q.emplace(0, 0);

        while (!empty(q)) {
            const auto u = cbegin(q)->second;
            q.erase(cbegin(q));

            for (const auto &[v, w] : g[u]) {
                if (D[u] + w < D[v]) {
                    q.erase({D[v], v});
                    D[v] = D[u] + w;
                    q.emplace(D[v], v);
                }
            }
        }

        cout << D[n - 1] << '\n';
    }
    return 0;
}
