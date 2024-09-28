#include <bits/stdc++.h>
using namespace std;

using ll = long long;

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

vector<int> toposort(const vector<vector<pii>> &g) {
    const auto n = sz(g);
    vector<int> indeg(n, 0);
    for (int u = 0; u < n; ++u) {
        for (const auto &[v, _] : g[u]) ++indeg[v];
    }

    queue<int> q;
    for (int u = 0; u < n; ++u) {
        if (!indeg[u]) q.push(u);
    }

    vector<int> result;
    result.reserve(n);

    while (!q.empty()) {
        const auto v = q.front();
        q.pop();
        result.push_back(v);

        for (const auto &[u, _] : g[v]) {
            --indeg[u];
            if (!indeg[u]) q.push(u);
        }
    }

    assert(sz(result) == n);
    return result;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int n, m;
    cin >> n >> m;

    vector<vector<pii>> g(n);
    vector<vector<pii>> g_(n);
    map<pii, int> weights;

    for (int i = 0; i < m; ++i) {
        int u, v, w;
        cin >> u >> v >> w;
        --u;
        --v;
        g[u].emplace_back(v, w);
        g_[v].emplace_back(u, w);
        weights.emplace(pii{u, v}, w);
    }

    const auto ord = toposort(g);
    vector<ll> result(n, 0);
    result[ord[0]] = 0;

    for (int i = 1; i < n; ++i) {
        const auto v = ord[i];

        if (g_[v].empty()) {
            result[v] = 0;
        } else {
            const auto [u, w] = g_[v][0];
            result[v] = result[u] + w;
        }
    }

    cout << result << '\n';
    return 0;
}
