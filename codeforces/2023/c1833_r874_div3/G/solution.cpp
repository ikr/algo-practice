#include <bits/stdc++.h>
using namespace std;

template <typename T> ostream &operator<<(ostream &os, const vector<T> &xs) {
    for (auto i = xs.cbegin(); i != xs.cend(); ++i) {
        if (i != xs.cbegin()) os << ' ';
        os << *i;
    }
    return os;
}

template <typename T1, typename T2>
ostream &operator<<(ostream &os, const pair<T1, T2> &x) {
    os << '(' << x.first << ' ' << x.second << ')';
    return os;
}

using pii = pair<int, int>;
using Graph = vector<vector<int>>;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

template <typename T> constexpr pair<T, T> normalized(const pair<T, T> &ab) {
    const auto [a, b] = ab;
    return {min(a, b), max(a, b)};
}

static constexpr int INF = 1'000'000'000;

optional<vector<int>> edges_cut(const Graph &g, const map<pii, int> &edge_ids) {
    if (sz(g) % 3) return nullopt;
    set<pii> es_cut;

    const auto weight_and_cut = [&](const auto self, const int u0,
                                    const int u) -> int {
        int subs{};
        for (const auto v : g[u]) {
            if (v == u0) continue;

            const auto sub = self(self, u, v);
            if (sub == INF) return INF;
            subs += sub;
        }

        if (subs == 2) {
            if (u0 != -1) es_cut.insert(normalized(pii{u0, u}));
            return 0;
        } else if (subs > 2) {
            return INF;
        }

        return subs + 1;
    };

    const auto root_weight = weight_and_cut(weight_and_cut, -1, 0);
    if (root_weight != 3 && root_weight != 0) return nullopt;

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

            g[u].push_back(v);
            g[v].push_back(u);
            edge_ids[normalized(pii{u, v})] = i;
        }

        const auto result = edges_cut(std::move(g), edge_ids);
        if (result) {
            cout << sz(*result) << '\n';
            cout << *result << '\n';
        } else {
            cout << "-1\n";
        }
    }

    return 0;
}
