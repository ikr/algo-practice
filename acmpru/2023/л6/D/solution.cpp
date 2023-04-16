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

vector<int> order_path(const vector<vector<pii>> &g, const vector<int> &vs) {
    set<int> vss(cbegin(vs), cend(vs));
    vector<int> ans;
    ans.reserve(sz(vs));

    const auto it0 = find_if(cbegin(g[0]), cend(g[0]), [&vss](const pii vc) {
        return vss.count(vc.first);
    });
    assert(it0 != cend(g[0]));

    ans.push_back(it0->first);
    vss.erase(it0->first);

    while (!vss.empty()) {
        const auto u = ans.back();
        const auto it = find_if(cbegin(g[u]), cend(g[u]), [&vss](const pii vc) {
            return vss.count(vc.first);
        });
        assert(it != cend(g[u]));

        ans.push_back(it->first);
        vss.erase(it->first);
    }

    return ans;
}

pii normalize(const pii ab) {
    const auto [a, b] = ab;
    return {min(a, b), max(a, b)};
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int n, m, q;
    cin >> n >> m >> q;

    atcoder::dsu dsu(n);
    map<pii, int> D;
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

        D[normalize({u, v})] = c;
    }

    auto ps = extract_paths(n, dsu.groups());
    for (auto &p : ps) p = order_path(g, p);

    map<int, ll> d0;
    map<int, ll> dn;
    map<int, int> idx;
    vector<ll> ds;
    ds.reserve(sz(ps));

    for (int i = 0; i < sz(ps); ++i) {
        for (const auto u : ps[i]) {
            idx[u] = i;
        }

        ds.push_back(D.at({0, ps[i][0]}));
        d0[ps[i][0]] = ds.back();

        for (int j = 1; j < sz(ps[i]); ++j) {
            const ll d = D.at(normalize({ps[i][j - 1], ps[i][j]}));
            ds.back() += d;
            d0[ps[i][j]] = d0[ps[i][j - 1]] + d;
        }

        const ll dr = D.at({ps[i].back(), n - 1});
        ds.back() += dr;
        dn[ps[i].back()] = dr;

        for (int j = sz(ps[i]) - 2; j >= 0; --j) {
            const ll d = D.at(normalize({ps[i][j], ps[i][j + 1]}));
            dn[ps[i][j]] = d0[ps[i][j + 1]] + d;
        }
    }

    const auto lo = *min_element(cbegin(ds), cend(ds));

    vector<ll> ans;
    ans.reserve(q);

    for (int query_num = 1; query_num <= q; ++query_num) {
        int x, y;
        cin >> x >> y;
        --x;
        --y;

        const auto r = [&]() -> ll {
            if (normalize({x, y}) == pii{0, n - 1}) return lo;

            if (x == 0) return min(d0.at(y), lo + dn.at(y));
            if (y == 0) return min(d0.at(x), lo + dn.at(x));
            if (x == n - 1) return min(dn.at(y), lo + d0.at(y));
            if (y == n - 1) return min(dn.at(x), lo + d0.at(x));

            if (idx.at(x) == idx.at(y)) {
                return abs(d0.at(x) - d0.at(y));
            }

            return min(d0.at(x) + d0.at(y), dn.at(x) + dn.at(y));
        }();

        ans.push_back(r);
    }

    cout << ans << '\n';
    return 0;
}
