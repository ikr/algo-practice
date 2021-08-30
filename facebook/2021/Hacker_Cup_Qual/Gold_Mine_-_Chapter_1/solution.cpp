#include <bits/stdc++.h>
using namespace std;

using vi = vector<int>;
using vvi = vector<vi>;
using pii = pair<int, int>;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

vector<set<int>> zero_rooted_tree(const vvi &g) {
    const int n = sz(g);
    vector<bool> visited(n, false);
    vector<set<int>> ans(n);

    function<void(int)> dfs;
    dfs = [&](const int u) {
        visited[u] = true;

        for (const auto v : g[u]) {
            if (visited[v]) continue;
            ans[u].insert(v);
            dfs(v);
        }
    };

    dfs(0);
    return ans;
}

vector<pii> one_way_yields_with_subroots(const vi &orz,
                                         const vector<set<int>> &tr) {
    vector<pii> ans(sz(orz), {-1, -1});
    ans[0] = {orz[0], -1};

    function<void(int, int)> recur;
    recur = [&](const int subroot, const int u) {
        for (const auto v : tr[u]) {
            ans[v] = {ans[u].first + orz[v], subroot};
            recur(subroot, v);
        }
    };

    for (const auto u : tr[0]) {
        ans[u] = {ans[0].first + orz[u], u};
        recur(u, u);
    }

    sort(rbegin(ans), rend(ans));
    return ans;
}

int max_yield(const vi &orz, const vvi &g) {
    const auto tr = zero_rooted_tree(g);
    if (sz(tr[0]) == 0) return orz[0];

    const auto ys = one_way_yields_with_subroots(orz, tr);
    const auto [a, subroot_a] = ys[0];
    if (sz(tr[0]) == 1) return a;

    int i = 0;
    while (ys[i].second == subroot_a) ++i;

    return a + ys[i].first - orz[0];
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t;
    cin >> t;
    for (int i = 1; i <= t; ++i) {
        int n;
        cin >> n;

        vi orz(n);
        for (auto &o : orz) cin >> o;

        vvi g(n);
        for (int j = 0; j < n - 1; ++j) {
            int a, b;
            cin >> a >> b;
            --a;
            --b;

            g[a].push_back(b);
            g[b].push_back(a);
        }

        cout << "Case #" << i << ": " << max_yield(orz, g) << '\n';
    }

    return 0;
}
