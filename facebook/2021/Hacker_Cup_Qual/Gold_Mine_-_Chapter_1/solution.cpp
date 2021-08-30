#include <bits/stdc++.h>
using namespace std;

using vi = vector<int>;
using vvi = vector<vi>;

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

int max_yield(const vi &os, const vvi &g) { return -1; }

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t;
    cin >> t;
    for (int i = 1; i <= t; ++i) {
        int n;
        cin >> n;

        vi os(n);
        for (auto &o : os) cin >> o;

        vvi g(n);
        for (int j = 0; j < n - 1; ++j) {
            int a, b;
            cin >> a >> b;
            --a;
            --b;

            g[a].push_back(b);
            g[b].push_back(a);
        }

        cout << "Case #" << i << ": " << max_yield(os, g) << '\n';
    }

    return 0;
}
