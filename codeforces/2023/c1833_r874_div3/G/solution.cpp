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

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

template <typename T> constexpr pair<T, T> normalized(const pair<T, T> &ab) {
    const auto [a, b] = ab;
    return {min(a, b), max(a, b)};
}

vector<int> degree(const vector<vector<int>> &g) {
    vector<int> result(sz(g), 0);
    for (int u = 0; u < sz(g); ++u) result[u] = sz(g[u]);
    return result;
}

queue<int> initial_frontier(const vector<int> &deg) {
    queue<int> result;
    for (int u{}; u < sz(deg); ++u) {
        if (deg[u] == 1) result.push(u);
    }
    return result;
}

optional<vector<int>> edges_cut(const vector<vector<int>> &g,
                                const map<pii, int> &edge_ids) {
    auto deg = degree(g);
    auto fro = initial_frontier(deg);
    set<int> vs_cut;
    set<pii> es_cut;

    map<int, int> mid;
    while (!fro.empty()) {
        const auto u = fro.front();
        fro.pop();

        for (const auto v : g[u]) {
            if (vs_cut.contains(v)) continue;

            if (mid.contains(v)) {

            } else {
            }
        }
    }

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
        vector<vector<int>> g(n);
        for (int i = 1; i <= n - 1; ++i) {
            int u, v;
            cin >> u >> v;
            --u;
            --v;

            g[u].push_back(v);
            g[v].push_back(u);
            edge_ids[normalized(pii{u, v})] = i;
        }

        const auto result = edges_cut(g, edge_ids);
        if (result) {
            cout << sz(*result) << '\n';
            cout << *result << '\n';
        } else {
            cout << "-1\n";
        }
    }

    return 0;
}
