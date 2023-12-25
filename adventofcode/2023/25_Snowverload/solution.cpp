#include <atcoder/dsu>
#include <bits/stdc++.h>
using namespace std;

using pii = pair<int, int>;

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

template <typename T>
ostream &operator<<(ostream &os, const vector<vector<T>> &xss) {
    for (const auto &xs : xss) os << xs << '\n';
    return os;
}

template <typename K, typename V>
ostream &operator<<(ostream &os, const map<K, V> &m) {
    os << '{';
    for (auto i = m.cbegin(); i != m.cend(); ++i) {
        if (i != m.cbegin()) os << ' ';
        os << '(' << i->first << ' ' << i->second << ')';
    }
    os << '}';
    return os;
}

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

vector<string> split(const string &delim_regex, const string &s) {
    regex r(delim_regex);
    return vector<string>(sregex_token_iterator(cbegin(s), cend(s), r, -1),
                          sregex_token_iterator{});
}

constexpr pii normalize(const pii ab) {
    return {min(ab.first, ab.second), max(ab.first, ab.second)};
}

optional<pii> find_bridge(const vector<vector<int>> &adj,
                          const set<pii> &skip_edges) {
    const auto n = sz(adj);
    optional<pii> result;
    vector<bool> visited(n, false);
    vector<int> tin(n, -1);
    vector<int> low(n, -1);
    int timer{};

    const auto recur = [&](const auto self, const int p, const int u) -> void {
        visited[u] = true;
        tin[u] = low[u] = timer++;
        for (const auto v : adj[u]) {
            if (v == p || skip_edges.contains(normalize({u, v}))) {
                continue;
            }

            if (visited[v]) {
                low[u] = min(low[u], tin[v]);
            } else {
                self(self, u, v);
                low[u] = min(low[u], low[v]);
                if (low[v] > tin[u]) {
                    result = normalize({u, v});
                }
            }
        }
    };

    for (int v = 0; v < n; ++v) {
        if (!visited[v]) recur(recur, -1, v);
    }

    return result;
}

int main() {
    vector<string> ids;
    map<string, int> codes_by_id;
    vector<pii> edges;

    const auto assigned_code = [&](const string &id) -> int {
        if (codes_by_id.contains(id)) return codes_by_id.at(id);
        codes_by_id.emplace(id, sz(ids));
        ids.push_back(id);
        return codes_by_id.at(id);
    };

    for (string line; getline(cin, line);) {
        const auto parts = split(": ", line);
        const auto tokens = split(" ", parts[1]);

        for (const auto &id : tokens) {
            auto u = assigned_code(parts[0]);
            auto v = assigned_code(id);
            cerr << parts[0] << " -> " << id << endl;
            edges.push_back(normalize({u, v}));
        }
    }
    ranges::sort(edges);

    cerr << "ids: " << ids << endl;
    cerr << "codes_by_id: " << codes_by_id << endl;
    cerr << sz(edges) << " edges: " << edges << endl << endl;

    const auto n = sz(ids);

    const auto components =
        [&](const set<int> &skip_edge_indices) -> vector<vector<int>> {
        atcoder::dsu dsu(n);
        for (int index = 0; index < sz(edges); ++index) {
            if (skip_edge_indices.contains(index)) continue;
            const auto [u, v] = edges[index];
            dsu.merge(u, v);
        }
        return dsu.groups();
    };

    cerr << "Initial components:\n" << components({}) << endl;

    vector<vector<int>> adj(n);
    for (const auto &[u, v] : edges) {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    const auto ijk = [&]() -> optional<tuple<int, int, int>> {
        for (int i = 0; i < sz(edges) - 1; ++i) {
            for (int j = i + 1; j < sz(edges); ++j) {
                const auto bridge = find_bridge(adj, {edges[i], edges[j]});
                if (bridge) {
                    const auto k =
                        inof(ranges::find(edges, *bridge) - cbegin(edges));
                    return tuple{i, j, k};
                }
            }
        }
        return nullopt;
    }();

    if (ijk) {
        const auto [i, j, k] = *ijk;
        cerr << "Found " << i << ' ' << j << ' ' << k << endl;

        const auto cs = components({i, j, k});
        cerr << cs << endl;
        assert(sz(cs) == 2);
        cout << sz(cs[0]) * sz(cs[1]) << '\n';
    } else {
        cerr << "Not found :(" << endl;
    }
    return 0;
}
