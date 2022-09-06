#include <bits/stdc++.h>
using namespace std;

using ll = long long;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

ll min_ops_cost(const vector<vector<int>> &g, const vector<int> &A) {
    set<pair<ll, int>> q;

    for (int u = 0; u < sz(A); ++u) {
        q.emplace(accumulate(cbegin(g[u]), cend(g[u]), 0LL,
                             [&A](const ll agg, const int v) -> ll {
                                 return agg + A[v];
                             }),
                  u);
    }

    vector<ll> idx(sz(A), -1);
    for (const auto &[c, u] : q) idx[u] = c;

    ll result{};

    while (!q.empty()) {
        const auto [cu, u] = *cbegin(q);
        q.erase(cbegin(q));
        idx[u] = -1;
        result = max(result, cu);

        for (const auto v : g[u]) {
            if (idx[v] == -1) continue;

            const auto it = q.find(pair{idx[v], v});
            assert(it != cend(q));
            q.erase(it);

            q.emplace(idx[v] - A[u], v);
            idx[v] -= A[u];
        }
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

    vector<vector<int>> g(N);
    for (int i = 1; i <= M; ++i) {
        int u, v;
        cin >> u >> v;
        --u;
        --v;

        g[u].push_back(v);
        g[v].push_back(u);
    }

    cout << min_ops_cost(g, A) << '\n';
    return 0;
}
