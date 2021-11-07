#include <atcoder/dsu>
#include <atcoder/modint>
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
    for (const auto xs : xss) os << xs << '\n';
    return os;
}

using ll = long long;
using vi = vector<int>;
using vvi = vector<vi>;
using pii = pair<int, int>;
using vll = vector<ll>;
using vvll = vector<vll>;
using mint = atcoder::modint998244353;

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

bool has_eulerian_trail(const vvi &g, const vi &us) {
    int od{};

    for (const auto u : us) {
        if (sz(g[u]) % 2) {
            ++od;
        }
    }

    return od == 0 || od == 2;
}

mint num_ways(const vvi &g, const vvi &cs) {
    if (any_of(cbegin(cs), cend(cs),
               [&g](const vi &us) { return sz(us) < 3; })) {
        return 0;
    }

    if (all_of(cbegin(cs), cend(cs),
               [&g](const vi &us) { return has_eulerian_trail(g, us); })) {
        return mint{2}.pow(sz(cs));
    }

    return 0;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    cout << setprecision(9) << fixed;

    int n, m;
    cin >> n >> m;

    vvi g(n);
    atcoder::dsu cs(n);

    for (int i = 0; i < m; ++i) {
        int u, v;
        cin >> u >> v;
        --u;
        --v;

        g[u].push_back(v);
        g[v].push_back(u);

        cs.merge(u, v);
    }

    cout << num_ways(g, cs.groups()).val() << '\n';
    return 0;
}
