#include <bits/stdc++.h>
using namespace std;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

template <typename T> ostream &operator<<(ostream &os, const vector<T> &xs) {
    os << '[';
    for (auto i = xs.cbegin(); i != xs.cend(); ++i) {
        if (i != xs.cbegin()) os << ' ';
        os << *i;
    }
    os << ']';
    return os;
}

vector<int> subtree_sizes(const vector<vector<int>> &g) {
    const int n = sz(g);
    vector<int> ans(n, -1);

    const auto recur = [&](const auto self, const int p, const int u) -> int {
        if (ans[u] != -1) return ans[u];
        return ans[u] = [&]() -> int {
            if (sz(g[u]) == 1 && g[u][0] == p) return 1;

            int cur{1};
            for (const auto v : g[u]) {
                if (v == p) continue;
                cur += self(self, u, v);
            }
            return cur;
        }();
    };

    recur(recur, -1, 0);
    return ans;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int N;
    cin >> N;

    vector<vector<int>> g(N);
    for (int i = 1; i <= N - 1; ++i) {
        int u, v;
        cin >> u >> v;
        --u;
        --v;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    const auto ss = subtree_sizes(g);
    int result{INT_MAX};
    for (const auto v : g[0]) {
        result = min(result, ss[v]);
    }
    cout << result << '\n';
    return 0;
}
