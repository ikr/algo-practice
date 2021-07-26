#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vi = vector<int>;
using vvi = vector<vi>;
using pii = pair<int, int>;
using vll = vector<ll>;
using vvll = vector<vll>;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}
template <typename T> constexpr ll llof(const T x) {
    return static_cast<ll>(x);
}
template <typename T> constexpr double doof(const T x) {
    return static_cast<double>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

int destinations_num(const vvi &g, const int origin) {
    int ans = 1;
    vector<bool> discovered(sz(g), false);
    discovered[origin] = true;

    function<void(int)> dfs;
    dfs = [&](const int u) {
        for (const auto v : g[u]) {
            if (discovered[v]) continue;
            discovered[v] = true;
            ++ans;
            dfs(v);
        }
    };

    dfs(origin);
    return ans;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    cout << setprecision(9) << fixed;

    int n, m;
    cin >> n >> m;

    vvi g(n);
    for (int i = 0; i < m; ++i) {
        int u, v;
        cin >> u >> v;
        --u;
        --v;
        g[u].push_back(v);
    }

    int ans = 0;
    for (int u = 0; u < n; ++u) {
        ans += destinations_num(g, u);
    }

    cout << ans << '\n';
    return 0;
}
