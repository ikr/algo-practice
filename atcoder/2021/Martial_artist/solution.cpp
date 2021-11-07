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

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    cout << setprecision(9) << fixed;

    int n;
    cin >> n;

    vll ts(n + 1, 0);
    vvi g(n + 1);

    for (int i = 1; i <= n; ++i) {
        cin >> ts[i];

        int k;
        cin >> k;

        for (int j = 1; j <= k; ++j) {
            int a;
            cin >> a;
            g[i].push_back(a);
        }
    }

    set<int> req;

    function<void(int)> dfs;
    dfs = [&](const int u) {
        for (const auto v : g[u]) {
            if (req.count(v)) continue;
            dfs(v);
        }
        req.insert(u);
    };
    dfs(n);

    ll ans{};

    for (const auto u : req) {
        ans += ts[u];
    }

    cout << ans << '\n';
    return 0;
}
