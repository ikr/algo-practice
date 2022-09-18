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

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

int completely_filled_in_the_end(const vector<vector<int>> &g,
                                 const vector<int> &xs) {
    const auto N = sz(g);
    vector<int> nums_by_level(N, 0);

    const auto dfs = [&](const auto self, const int l, const int parent,
                         const int u) -> void {
        ++nums_by_level[l];

        for (const auto v : g[u]) {
            if (v == parent) continue;
            self(self, l + 1, u, v);
        }
    };
    dfs(dfs, 0, -1, 0);

    int result{};
    int cur = sz(xs);

    for (const auto k : nums_by_level) {
        if (k > cur) break;
        cur -= k;
        result += k;
    }

    return result;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t;
    cin >> t;
    for (int i = 1; i <= t; ++i) {
        int N, Q;
        cin >> N >> Q;

        vector<vector<int>> g(N);
        for (int j = 1; j <= N - 1; ++j) {
            int u, v;
            cin >> u >> v;
            --u;
            --v;

            g[u].push_back(v);
            g[v].push_back(u);
        }

        vector<int> xs(Q);
        for (auto &x : xs) cin >> x;

        cout << "Case #" << i << ": " << completely_filled_in_the_end(g, xs)
             << '\n';
    }

    return 0;
}
