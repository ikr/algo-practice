#include <bits/stdc++.h>
using namespace std;

template <typename T> ostream &operator<<(ostream &os, const vector<T> &xs) {
    for (auto i = xs.cbegin(); i != xs.cend(); ++i) {
        if (i != xs.cbegin()) os << ' ';
        os << *i;
    }
    return os;
}

using pii = pair<int, int>;
using tri = tuple<int, int, int>;
using Graph = vector<set<int>>;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

template <typename T> constexpr pair<T, T> normalized(const pair<T, T> &ab) {
    const auto [a, b] = ab;
    return {min(a, b), max(a, b)};
}

vector<int> degree(const Graph &g) {
    vector<int> result(sz(g), 0);
    for (int u = 0; u < sz(g); ++u) result[u] = sz(g[u]);
    return result;
}

vector<int> initial_frontier(const vector<int> &deg) {
    vector<int> result;
    for (int u{}; u < sz(deg); ++u) {
        if (deg[u] == 1) result.push_back(u);
    }
    return result;
}

optional<vector<int>> edges_cut(Graph g, const map<pii, int> &edge_ids) {
    auto deg = degree(g);
    auto fro = initial_frontier(deg);

    const auto angular_vetochkas = [&]() -> vector<tri> {
        vector<tri> result;
        map<int, int> mi;

        for (const auto u : fro) {
            for (const auto v : g[u]) {
                if (mi.contains(v)) {

                } else {
                }
            }
        }

        return result;
    };

    set<pii> es_cut;

    // ??

    vector<int> result;
    for (const auto &e : es_cut) result.push_back(edge_ids.at(e));
    return result;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;

        map<pii, int> edge_ids;
        Graph g(n);
        for (int i = 1; i <= n - 1; ++i) {
            int u, v;
            cin >> u >> v;
            --u;
            --v;

            g[u].insert(v);
            g[v].insert(u);
            edge_ids[normalized(pii{u, v})] = i;
        }

        const auto result = edges_cut(move(g), edge_ids);
        if (result) {
            cout << sz(*result) << '\n';
            cout << *result << '\n';
        } else {
            cout << "-1\n";
        }
    }

    return 0;
}
