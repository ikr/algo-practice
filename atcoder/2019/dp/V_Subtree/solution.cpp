#include <atcoder/modint>
#include <atcoder/segtree>
#include <bits/stdc++.h>
using namespace std;

using mint = atcoder::modint;

mint op(const mint a, const mint b) { return a * b; }
mint e() { return -1; }

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

vector<mint> num_ways(const vector<vector<int>> &g) {
    vector<atcoder::segtree<mint, op, e>> subtrees;
    subtrees.reserve(sz(g));
    for (int u = 0; u < sz(subtrees); ++u) {
        subtrees.emplace_back(atcoder::segtree<mint, op, e>(sz(g[u])));
    }

    vector<int> parent_(sz(g), -1);

    const auto recur = [&](const auto &self, const int p, const int u) -> void {
        parent_[u] = p;

        for (int i = 0; i < sz(g[u]); ++i) {
            const auto v = g[u][i];
            if (v == p) continue;
            self(self, u, v);

            if (empty(g[v])) continue;
            subtrees[u].set(i, subtrees[v].all_prod() + 1);
        }
    };
    recur(recur, -1, 0);

    vector<mint> result(sz(g), 0);
    for (int u = 0; u < sz(g); ++u) {
        result[u] = empty(g[u]) ? 1 : subtrees[u].all_prod();
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
