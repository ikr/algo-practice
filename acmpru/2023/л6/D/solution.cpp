#include <atcoder/dsu>
#include <bits/stdc++.h>
using namespace std;

using pii = pair<int, int>;
using ll = long long;

template <typename T> ostream &operator<<(ostream &os, const vector<T> &xs) {
    for (auto i = xs.cbegin(); i != xs.cend(); ++i) {
        if (i != xs.cbegin()) os << ' ';
        os << *i;
    }
    return os;
}

template <typename T>
ostream &operator<<(ostream &os, const vector<vector<T>> &xss) {
    for (const auto &xs : xss) os << xs << '\n';
    return os;
}

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

vector<vector<int>> extract_paths(const int n, vector<vector<int>> cs) {
    const auto it = remove_if(begin(cs), end(cs), [n](const vector<int> &xs) {
        return sz(xs) == 1 && (xs[0] == 0 || xs[0] == n - 1);
    });
    cs.erase(it, end(cs));

    return cs;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int n, m, q;
    cin >> n >> m >> q;

    atcoder::dsu dsu(n);

    vector<vector<pii>> g(n);
    for (int i = 1; i <= m; ++i) {
        int u, v, c;
        cin >> u >> v >> c;
        --u;
        --v;

        g[u].emplace_back(v, c);
        g[v].emplace_back(u, c);

        if (u && u != n - 1 && v && v != n - 1) {
            dsu.merge(u, v);
        }
    }

    vector<ll> ans;
    ans.reserve(q);

    for (int query_num = 1; query_num <= q; ++query_num) {
        int x, y;
        cin >> x >> y;
        --x;
        --y;

        ans.push_back(x * y);
    }

    cout << ans << '\n';

    cerr << endl << extract_paths(n, dsu.groups()) << endl;
    return 0;
}
