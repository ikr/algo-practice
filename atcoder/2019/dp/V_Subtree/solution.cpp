#include <atcoder/modint>
#include <bits/stdc++.h>
using namespace std;

using mint = atcoder::modint;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

vector<mint> num_ways(const vector<vector<int>> &g) {
    vector<int> ancestors(sz(g), -1);
    vector<int> descendants(sz(g), -1);

    const auto recur = [&](const auto &self, const int parent,
                           const int u) -> void {
        ancestors[u] = parent == -1 ? 0 : (ancestors[parent] + 1);
        descendants[u] = 0;

        for (const auto v : g[u]) {
            if (v == parent) continue;
            self(self, u, v);
            descendants[u] += descendants[v] + 1;
        }
    };
    recur(recur, -1, 0);

    vector<mint> result(sz(g), 0);
    for (int i = 0; i < sz(result); ++i) {
        result[i] = mint{ancestors[i] + 1} * mint{descendants[i] + 1};
    }
    return result;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int N, M;
    cin >> N >> M;
    mint::set_mod(M);

    vector<vector<int>> g(N);

    for (int i = 1; i <= N - 1; ++i) {
        int x, y;
        cin >> x >> y;
        --x;
        --y;

        g[x].push_back(y);
        g[y].push_back(x);
    }

    for (const auto x : num_ways(g)) cout << x.val() << '\n';
    return 0;
}
