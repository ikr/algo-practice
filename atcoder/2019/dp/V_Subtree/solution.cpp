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
    const auto subtrees_num = [&](const auto &self, const int p,
                                  const int u) -> mint {
        mint result{1};
        for (const auto v : g[u]) {
            if (v == p) continue;
            result *= self(self, u, v) + 1;
        }
        return result;
    };

    vector<mint> D(sz(g), 0);
    for (int u = 0; u < sz(g); ++u) D[u] = subtrees_num(subtrees_num, u, u);
    return D;
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
