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

template <typename T1, typename T2>
ostream &operator<<(ostream &os, const pair<T1, T2> &x) {
    os << '(' << x.first << ' ' << x.second << ')';
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

using pii = pair<int, int>;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

bool satisfies(const vector<vector<int>> &g, const vector<vector<int>> &cs,
               const map<pii, int> &ef) {
    // cerr << "g:" << g << " cs:" << cs << endl;

    for (const auto &us : cs) {
        set<pii> edges;

        for (const int u : us) {
            for (const int v : g[u]) {
                if (u > v) {
                    edges.emplace(v, u);
                } else {
                    edges.emplace(u, v);
                }
            }
        }

        int es{};
        for (const auto &uv : edges) {
            es += ef.at(uv);
        }

        // cerr << "edges:" << edges << endl;
        if (es != sz(us)) return false;
    }

    return true;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int N, M;
    cin >> N >> M;

    vector<vector<int>> g(N);
    atcoder::dsu uf(N);
    map<pii, int> ef;

    for (int i = 1; i <= M; ++i) {
        int u, v;
        cin >> u >> v;
        --u;
        --v;

        uf.merge(u, v);
        g[u].push_back(v);
        g[v].push_back(u);

        ++ef[pii{min(u, v), max(u, v)}];
    }

    cout << (satisfies(g, uf.groups(), ef) ? "Yes" : "No") << '\n';
    return 0;
}
