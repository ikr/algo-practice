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
template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

template <typename T> ostream &operator<<(ostream &os, const vector<T> &xs) {
    os << '[';
    for (auto i = xs.cbegin(); i != xs.cend(); ++i) {
        if (i != xs.cbegin()) os << ' ';
        os << *i;
    }
    os << ']';
    return os;
}

vi all_leaves(const vvi &g) {
    vi ans;

    for (int u = 0; u < sz(g); ++u) {
        if (sz(g[u]) <= 1) ans.push_back(u);
    }

    return ans;
}

int vertices_num_after_k_ops(const vvi &g, const int k) {
    vi deg(sz(g), 0);
    for (const auto u : all_leaves(g)) {
        deg[u] = 1;
    }

    vector<bool> visited(sz(g), false);
    function<int(int)> recur;
    recur = [&](const int u) -> int {
        if (deg[u]) return deg[u];

        int ans{};

        for (const auto v : g[u]) {
            if (visited[v]) continue;
            visited[v] = true;
            ans = max(ans, 1 + recur(v));
        }

        deg[u] = ans;
        return ans;
    };

    for (int u = 0; u < sz(g); ++u) {
        fill(begin(visited), end(visited), false);
        visited[u] = true;
        recur(u);
    }

    return count_if(cbegin(deg), cend(deg), [k](const int d) { return d > k; });
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t;
    cin >> t;
    while (t--) {
        int n, k;
        cin >> n >> k;

        vvi g(n);
        for (int i = 1; i <= n - 1; ++i) {
            int u, v;
            cin >> u >> v;
            --u;
            --v;

            g[u].push_back(v);
            g[v].push_back(u);
        }

        cout << vertices_num_after_k_ops(g, k) << '\n';
    }

    return 0;
}
