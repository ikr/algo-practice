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

optional<vector<int>> edges_cut(const vector<vector<int>> &g,
                                const map<pii, int> &edge_indices) {
    return vector<int>{};
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;

        map<pii, int> edge_indices;
        vector<vector<int>> g(n);
        for (int i = 1; i <= n - 1; ++i) {
            int u, v;
            cin >> u >> v;
            --u;
            --v;

            g[u].push_back(v);
            g[v].push_back(u);
            edge_indices[normalized(pii{u, v})] = i;
        }

        const auto result = edges_cut(g, edge_indices);
        if (result) {
            cout << sz(*result) << '\n';
            cout << *result << '\n';
        } else {
            cout << "-1\n";
        }
    }

    return 0;
}
