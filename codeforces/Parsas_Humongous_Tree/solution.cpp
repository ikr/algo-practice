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

template <typename T> T max_in(const pair<T, T> &xy) {
    const auto [x, y] = xy;
    return max(x, y);
}

ll max_beauty(const vector<pii> &ranges, const vvi &g) {
    const auto t = zero_rooted_tree(g);
    vector<pair<ll, ll>> dp(sz(g), {0, 0});

    function<void(int)> recur;
    recur = [&](const int u) {
        const auto [u_lo, u_hi] = ranges[u];

        for (const auto v : t[u]) {
            const auto [v_lo, v_hi] = ranges[v];

            dp[v] = {max_in(dp[u]) + max(abs(v_lo - u_lo), abs(v_lo - u_hi)),
                     max_in(dp[u]) + max(abs(v_hi - u_lo), abs(v_hi - u_hi))};

            recur(v);
        }
    };

    recur(0);
    cerr << dp << endl;

    ll ans = 0;
    for (const auto u : leaves(t)) {
        const auto [o1, o2] = dp[u];
        ans += max(o1, o2);
    }
    return ans;
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
