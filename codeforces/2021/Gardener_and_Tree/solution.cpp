#include <bits/stdc++.h>
using namespace std;

using vi = vector<int>;
using vvi = vector<vi>;
using pii = pair<int, int>;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

vi all_leaves(const vvi &g) {
    vi ans;

    for (int u = 0; u < sz(g); ++u) {
        if (sz(g[u]) <= 1) ans.push_back(u);
    }

    return ans;
}

vi all_degrees(const vvi &g) {
    vi ans(sz(g), 0);
    for (int u = 0; u < sz(g); ++u) {
        ans[u] = sz(g[u]);
    }
    return ans;
}

int vertices_num_after_k_ops(const vvi &g, const int k) {
    if (sz(g) < 3) return 0;

    auto deg = all_degrees(g);
    queue<pii> q;
    set<int> qd;

    int step = 1;
    for (const auto u : all_leaves(g)) {
        q.emplace(u, step);
        qd.insert(u);
    }

    while (!q.empty() && step <= k) {
        const auto [u, t] = q.front();
        if (t > step) {
            ++step;
            continue;
        }
        q.pop();

        deg[u] = -1;

        for (const auto v : g[u]) {
            --deg[v];
            if (deg[v] <= 1 && !qd.count(v)) {
                q.emplace(v, step + 1);
                qd.insert(v);
            }
        }
    }

    return inof(
        count_if(cbegin(deg), cend(deg), [](const int x) { return x >= 0; }));
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t;
    cin >> t;
    while (t--) {
        int n, k;
        cin >> n >> k;

        vvi g(n);
        for (int i = 1; i <= n - 1; ++i) {
            int u, v;
            cin >> u >> v;
            --u;
            --v;

            g[u].push_back(v);
            g[v].push_back(u);
        }

        cout << vertices_num_after_k_ops(g, k) << '\n';
    }

    return 0;
}
