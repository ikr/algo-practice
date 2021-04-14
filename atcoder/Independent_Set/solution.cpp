#include <bits/stdc++.h>
using namespace std;

using vi = vector<int>;
using pii = pair<int, int>;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

static constexpr int M = 1e9 + 7;
using Graph = multimap<int, int>;

int num_ways(const int n, const Graph &g) {
    vector<bool> discovered(n, false);
    vector<pii> dp(n, {0, 0});
    dp[0] = {1, 1}; // black, white

    function<void(int)> dfs;
    dfs = [&](const int u) {
        discovered[u] = true;
        const auto [first, last] = g.equal_range(u);

        for (auto it = first; it != last; ++it) {
            const int v = it->second;
            if (discovered[v]) continue;

            const auto [ub, uw] = dp[u];
            dp[v] = {uw, (ub + uw) % M};

            dfs(v);
        }
    };

    dfs(0);
    return (dp.back().first + dp.back().second) % M;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int n;
    cin >> n;

    Graph g;
    for (int i = 1; i < n; ++i) {
        int u, v;
        cin >> u >> v;
        --u;
        --v;

        g.emplace(u, v);
        g.emplace(v, u);
    }

    cout << num_ways(n, g) << '\n';
    return 0;
}
