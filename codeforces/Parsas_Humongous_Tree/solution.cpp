#include <bits/stdc++.h>
using namespace std;

template <typename T> ostream &operator<<(ostream &os, const vector<T> &xs) {
    os << '[';
    for (auto i = xs.cbegin(); i != xs.cend(); ++i) {
        if (i != xs.cbegin()) os << ' ';
        os << *i;
    }
    os << ']';
    return os;
}

template <typename T> ostream &operator<<(ostream &os, const set<T> &xs) {
    os << '{';
    for (auto i = xs.cbegin(); i != xs.cend(); ++i) {
        if (i != xs.cbegin()) os << ' ';
        os << *i;
    }
    os << '}';
    return os;
}

using ll = long long;
using vi = vector<int>;
using vvi = vector<vi>;
using pii = pair<int, int>;
using vll = vector<ll>;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}
template <typename T> constexpr ll llof(const T x) {
    return static_cast<ll>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

using Tree = vector<set<int>>;

Tree zero_rooted_tree(const vvi &g) {
    Tree ans(sz(g));
    vector<bool> discovered(sz(g), false);

    function<void(int)> dfs;
    dfs = [&](const int u) {
        for (const auto v : g[u]) {
            if (discovered[v]) continue;
            discovered[v] = true;
            ans[u].insert(v);
            dfs(v);
        }
    };

    discovered[0] = true;
    dfs(0);
    return ans;
}

vi leaves(const Tree &t) {
    vi ans;
    for (int i = 0; i < sz(t); ++i) {
        if (t[i].empty()) ans.push_back(i);
    }
    return ans;
}

ll max_beauty(const vector<pii> &ranges, const vvi &g) {
    vector<pair<ll, ll>> dp(sz(g), {0, 0});
    return -1;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;

        vector<pii> ranges(n);
        for (auto &[lo, hi] : ranges) cin >> lo >> hi;

        vvi g(n);
        for (int i = 0; i < n - 1; ++i) {
            int u, v;
            cin >> u >> v;
            --u;
            --v;

            g[u].push_back(v);
            g[v].push_back(u);
        }

        cout << max_beauty(ranges, g) << '\n';
    }

    return 0;
}
