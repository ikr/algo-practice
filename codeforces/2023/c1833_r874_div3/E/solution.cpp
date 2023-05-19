#include <atcoder/dsu>
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

template <typename T>
ostream &operator<<(ostream &os, const vector<vector<T>> &xss) {
    for (const auto &xs : xss) os << xs << '\n';
    return os;
}

using pii = pair<int, int>;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

pii lo_and_hi(const vector<vector<int>> &cs, const vector<int> &deg) {
    // cerr << "deg: " << deg << " cs: " << cs << endl;
    vector<bool> is_pluggable(sz(cs), false);
    transform(cbegin(cs), cend(cs), begin(is_pluggable),
              [&](const vector<int> &vs) {
                  return inof(count_if(cbegin(vs), cend(vs), [&](const int v) {
                             return deg[v] == 1;
                         })) >= 2;
              });

    const auto pluggable =
        count(cbegin(is_pluggable), cend(is_pluggable), true);

    const auto non_pluggable = sz(cs) - pluggable;

    if (pluggable == 0) return {sz(cs), sz(cs)};
    if (non_pluggable == 0) return {1, sz(cs)};
    return {non_pluggable + 1, sz(cs)};
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;

        atcoder::dsu uf(n);
        vector<set<int>> g(n);

        for (int u = 0; u < n; ++u) {
            int v;
            cin >> v;
            --v;

            uf.merge(u, v);
            g[u].insert(v);
            g[v].insert(u);
        }

        vector<int> deg(n, 0);
        for (int u = 0; u < n; ++u) {
            deg[u] = sz(g[u]);
        }

        const auto [lo, hi] = lo_and_hi(uf.groups(), deg);
        cout << lo << ' ' << hi << '\n';
    }

    return 0;
}
