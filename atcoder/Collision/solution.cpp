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

vi gather_levels(const vvi &g) {
    const int n = sz(g);
    vi ans(n, -1);
    ans[0] = 0;

    function<void(int, int)> dfs;
    dfs = [&](const int level, const int u) {
        for (const auto v : g[u]) {
            if (ans[v] != -1) continue;
            ans[v] = level + 1;
            dfs(level + 1, v);
        }
    };

    dfs(0, 0);
    return ans;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    cout << setprecision(9) << fixed;

    int n, q;
    cin >> n >> q;

    vvi g(n);
    for (int i = 1; i <= n - 1; ++i) {
        int a, b;
        cin >> a >> b;
        --a;
        --b;

        g[a].push_back(b);
        g[b].push_back(a);
    }

    vector<pii> qs(q);
    for (auto &[c, d] : qs) {
        cin >> c >> d;
        --c;
        --d;
    }

    const auto ls = gather_levels(g);

    for (const auto [u, v] : qs) {
        const auto delta = abs(ls[u] - ls[v]);
        cout << ((delta % 2) ? "Road" : "Town") << '\n';
    }

    return 0;
}
