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

using ll = long long;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

map<int, int> gather_freqs(const vector<int> &xs) {
    map<int, int> result;
    for (const auto x : xs) ++result[x];
    return result;
}

vector<int> topo_sort(const vector<vector<int>> &adj) {
    const auto n = sz(adj);
    vector<bool> visited(n, false);
    vector<int> ans;
    ans.reserve(n);

    const auto dfs = [&](const auto self, const int v) -> void {
        visited[v] = true;

        for (int u : adj[v]) {
            if (!visited[u]) {
                self(self, u);
            }
        }
        ans.push_back(v);
    };

    for (int i = 0; i < n; ++i) {
        if (!visited[i]) {
            dfs(dfs, i);
        }
    }

    reverse(ans.begin(), ans.end());
    return ans;
}

ll min_remaining_sum(const vector<int> &A, const int M) {
    const auto fs = gather_freqs(A);

    vector<int> vert;
    vert.reserve(sz(fs));
    for (const auto [a, _] : fs) {
        vert.push_back(a);
    }

    map<int, int> idx;
    for (int i = 0; i < sz(vert); ++i) {
        idx[vert[i]] = i;
    }

    vector<vector<int>> g(sz(vert));
    for (int u = 0; u < sz(vert); ++u) {
        if (idx.count((vert[u] + 1) % M)) {
            const auto v = idx.at((vert[u] + 1) % M);
            g[u].push_back(v);
        }
    }

    const auto is_adj = [&](const int u, const int v) -> bool {
        return find(cbegin(g[u]), cend(g[u]), v) != cend(g[u]);
    };

    const auto topo = topo_sort(g);
    cerr << "fs: " << fs << " vert: " << vert << " g: " << g
         << " topo: " << topo << '\n';

    vector<vector<int>> par(1, vector<int>{topo[0]});

    for (int i = 1; i < sz(topo); ++i) {
        if (is_adj(topo[i - 1], topo[i])) {
            par.back().push_back(topo[i]);
        } else {
            par.push_back(vector<int>{topo[i]});
        }
    }

    ll result = LONG_LONG_MAX;
    for (const auto &us : par) {
        ll cur{};

        for (const auto u : us) {
            cur += 1LL * vert[u] * fs.at(vert[u]);
        }

        result = min(result, cur);
    }
    return result;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int N, M;
    cin >> N >> M;

    vector<int> A(N);
    for (auto &a : A) cin >> a;

    cout << min_remaining_sum(A, M) << '\n';
    return 0;
}
