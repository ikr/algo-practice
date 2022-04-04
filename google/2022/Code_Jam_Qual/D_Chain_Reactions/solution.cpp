#include <algorithm>
#include <cassert>
#include <iostream>
#include <vector>
using namespace std;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

vector<vector<int>> children_sorted(const vector<int> &F,
                                    const vector<int> &P) {
    vector<vector<int>> result(sz(P));
    for (int u = 0; u < sz(P); ++u) {
        if (P[u] >= 0) result[P[u]].push_back(u);
    }
    for (auto &ch : result) {
        sort(begin(ch), end(ch),
             [&](const int u, const int v) { return F[u] < F[v]; });
    }
    return result;
}

int max_fun(const vector<int> &F, const vector<int> &P) {
    const auto ch = children_sorted(F, P);
    vector<int> ordering;
    vector<bool> visited(sz(P), false);
    const auto dfs = [&](const auto self, const int u) -> void {
        visited[u] = true;
        if (ch[u].empty()) {
            ordering.push_back(u);
        } else {
            for (const auto v : ch[u]) self(self, v);
        }
    };
    for (int u = 0; u < sz(P); ++u) {
        if (!visited[u]) dfs(dfs, u);
    }

    int result{};
    vector<bool> used(sz(P), false);
    for (const auto u : ordering) {
        assert(!used[u]);
        int hi = F[u];
        auto v = u;

        while (v >= 0 && !used[v]) {
            used[v] = true;
            hi = max(hi, F[v]);
            v = P[v];
        }

        result += hi;
    }
    return result;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t;
    cin >> t;
    for (int i = 1; i <= t; ++i) {
        int N;
        cin >> N;

        vector<int> F(N);
        for (auto &f : F) cin >> f;

        vector<int> P(N);
        for (auto &p : P) {
            cin >> p;
            --p;
        }

        cout << "Case #" << i << ": " << max_fun(F, P) << '\n';
    }

    return 0;
}
