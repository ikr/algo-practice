#include <bits/stdc++.h>
using namespace std;

using ll = long long;
static constexpr ll M = 1e9 + 7;
using Graph = multimap<int, int>;

ll num_ways(const int n, const Graph &g) {
    vector<bool> discovered(n, false);
    vector<pair<ll, ll>> dp(n, {1, 1}); // black, white

    function<void(int)> dfs;
    dfs = [&](const int u) {
        discovered[u] = true;
        const auto [first, last] = g.equal_range(u);

        for (auto it = first; it != last; ++it) {
            const int v = it->second;
            if (discovered[v]) continue;

            dfs(v);

            dp[u].first *= dp[v].second;
            dp[u].first %= M;

            dp[u].second *= dp[v].first + dp[v].second;
            dp[u].second %= M;
        }
    };

    dfs(0);
    return (dp[0].first + dp[0].second) % M;
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
