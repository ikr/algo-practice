#include <bits/stdc++.h>
using namespace std;

using pii = pair<int, int>;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

bool is_possible(const vector<vector<pii>> &g, const int a, const int b) {
    const auto yields_from_x = [&](const int x, const int skip) -> set<int> {
        set<int> result;

        const auto dfs = [&](const auto self, const int cur,
                             const pii uu) -> void {
            const auto [u_, u] = uu;

            for (const auto &[v, w] : g[u]) {
                if (v == u_) continue;
                if (v != skip) result.insert(cur ^ w);
                self(self, cur ^ w, {u, v});
            }
        };

        dfs(dfs, 0, {-1, x});

        return result;
    };

    const auto yields_from_b = yields_from_x(b, -1);
    if (yields_from_b.contains(0)) return true;

    for (const auto x : yields_from_x(a, b)) {
        if (yields_from_b.contains(x)) return true;
    }

    return false;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t;
    cin >> t;
    while (t--) {
        int n, a, b;
        cin >> n >> a >> b;
        --a;
        --b;

        vector<vector<pii>> g(n);
        for (int i = 1; i <= n - 1; ++i) {
            int u, v, w;
            cin >> u >> v >> w;
            --u;
            --v;

            g[u].emplace_back(v, w);
            g[v].emplace_back(u, w);
        }

        cout << (is_possible(g, a, b) ? "YES" : "NO") << '\n';
    }

    return 0;
}
