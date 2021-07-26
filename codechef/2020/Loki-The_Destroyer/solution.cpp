#include <bits/stdc++.h>
using namespace std;
using Ints = vector<int>;
using Graph = unordered_multimap<int, int>;
using ll = long long;
static constexpr ll M = 1e9 + 7;

Ints mark_components(const int n, const Graph &g) {
    int curr = -1;
    Ints ans(n, -1);

    function<void(int)> dfs;
    dfs = [&dfs, &g, &curr, &ans](const int x) {
        ans[x] = curr;
        const auto [first, last] = g.equal_range(x);
        for (auto it = first; it != last; ++it) {
            if (ans[it->second] == -1) dfs(it->second);
        }
    };

    for (int i = 0; i < n; ++i) {
        if (ans[i] >= 0) continue;
        ++curr;
        dfs(i);
    }

    return ans;
}

ll solve(const Ints &rs, const Graph &g) {
    const int n = rs.size();
    const auto cs = mark_components(n, g);
    const unordered_set<int> distinct_components(cbegin(cs), cend(cs));

    vector<multiset<int>> risks_by_component(distinct_components.size(),
                                             multiset<int>{});

    for (int i = 0; i < n; ++i) {
        risks_by_component[cs[i]].insert(rs[i]);
    }

    ll ans = 1;

    for (const auto &rs : risks_by_component) {
        assert(!rs.empty());
        const int min_risk = *cbegin(rs);
        ans *= rs.count(min_risk);
        ans %= M;
    }

    return ans;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n;
    cin >> n;
    Ints rs(n, 0);
    for (auto &r : rs) cin >> r;

    int edges_count;
    cin >> edges_count;
    Graph g;
    for (int i = 0; i < edges_count; ++i) {
        int u, v;
        cin >> u >> v;
        --u;
        --v;
        g.emplace(u, v);
        g.emplace(v, u);
    }

    cout << solve(rs, g) << '\n';
    return 0;
}
