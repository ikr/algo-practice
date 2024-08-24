#include <bits/stdc++.h>
using namespace std;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

template <typename T> ostream &operator<<(ostream &os, const set<T> &xs) {
    os << '{';
    for (auto i = xs.cbegin(); i != xs.cend(); ++i) {
        if (i != xs.cbegin()) os << ' ';
        os << *i;
    }
    os << '}';
    return os;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int n, k;
    cin >> n >> k;

    vector<vector<int>> g(n);
    for (int i = 1; i <= n - 1; ++i) {
        int u, v;
        cin >> u >> v;
        --u;
        --v;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    set<int> req;
    for (int i = 0; i < k; ++i) {
        int u;
        cin >> u;
        --u;
        req.insert(u);
    }

    const auto recur = [&](const auto self, const int p, const int u) -> void {
        for (const auto v : g[u]) {
            if (p == v) continue;
            self(self, u, v);
        }

        if (req.contains(u) ||
            any_of(cbegin(g[u]), cend(g[u]),
                   [&](const int v) { return p != v && req.contains(v); })) {
            req.insert(u);
        }
    };

    recur(recur, -1, *cbegin(req));
    cout << sz(req) << '\n';
    return 0;
}
