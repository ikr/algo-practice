#include <atcoder/dsu>
#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vi = vector<int>;
using vvi = vector<vi>;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

ll component_rgb_paintings_num(const int start, const int comp_size,
                               const vvi &g) {
    vi coloring(sz(g), 0);

    function<ll(int, int, int)> dfs;
    dfs = [&](const int colored_num, const int u, const int color) -> ll {
        for (const int v : g[u]) {
            if (coloring[v] == color) return 0;
        }

        if (colored_num + 1 == comp_size) return 1;

        ll ans = 0;
        coloring[u] = color;
        for (const int v : g[u]) {
            if (coloring[v]) continue;

            for (int color_ = 1; color_ <= 3; ++color_) {
                if (color_ == color) continue;
                ans += dfs(colored_num + 1, v, color_);
            }
        }
        return ans;
    };

    ll ans = 0;
    ans += dfs(0, start, 1);
    fill(begin(coloring), end(coloring), 0);
    ans += dfs(0, start, 2);
    fill(begin(coloring), end(coloring), 0);
    ans += dfs(0, start, 3);
    return ans;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int n, m;
    cin >> n >> m;

    vvi g(n);
    atcoder::dsu comps(n);

    while (m--) {
        int a, b;
        cin >> a >> b;
        --a;
        --b;

        g[a].push_back(b);
        g[b].push_back(a);
        comps.merge(a, b);
    }

    set<int> leaders;
    for (int i = 0; i < n; ++i) leaders.insert(comps.leader(i));

    ll ans = 1;
    for (const auto u : leaders) {
        ans *= component_rgb_paintings_num(u, comps.size(u), g);
    }

    cout << ans << '\n';
    return 0;
}
