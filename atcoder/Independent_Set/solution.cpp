#include <bits/stdc++.h>
using namespace std;

template <typename T1, typename T2>
ostream &operator<<(ostream &os, const pair<T1, T2> &x) {
    os << '(' << x.first << ' ' << x.second << ')';
    return os;
}

template <typename T> ostream &operator<<(ostream &os, const vector<T> &xs) {
    os << '[';
    for (auto i = xs.cbegin(); i != xs.cend(); ++i) {
        if (i != xs.cbegin()) os << ' ';
        os << *i;
    }
    os << ']';
    return os;
}

using vi = vector<int>;
using pii = pair<int, int>;

static constexpr int M = 1e9 + 7;
using Graph = multimap<int, int>;

int num_ways(const int n, const Graph &g) {
    vector<bool> discovered(n, false);
    vector<pii> dp(n, {1, 1}); // black, white

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
    cerr << dp << '\n';
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
