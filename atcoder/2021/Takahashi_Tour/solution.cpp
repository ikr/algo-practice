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

vi traversal(const vvi &g) {
    const int n = sz(g);
    vi ans;
    vector<bool> discovered(n, false);
    ans.reserve(2 * n - 1);

    function<void(int)> dfs;
    dfs = [&](const int u) {
        ans.push_back(u);
        discovered[u] = true;

        for (const auto v : g[u]) {
            if (discovered[v]) continue;
            dfs(v);
            ans.push_back(u);
        }
    };

    dfs(0);
    return ans;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    cout << setprecision(9) << fixed;

    int n;
    cin >> n;

    vvi g(n);
    for (int i = 0; i < n - 1; ++i) {
        int a, b;
        cin >> a >> b;
        --a;
        --b;

        g[a].push_back(b);
        g[b].push_back(a);
    }

    for (auto &adj : g) {
        sort(begin(adj), end(adj));
    }

    for (const auto u : traversal(g)) {
        cout << (u + 1) << ' ';
    }
    cout << '\n';
    return 0;
}
