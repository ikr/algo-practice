#include <atcoder/modint>
#include <bits/stdc++.h>
using namespace std;

using mint = atcoder::modint;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

vector<mint> num_ways(const vector<vector<int>> &g) {
    vector<mint> down(sz(g), 0);
    vector<int> parent(sz(g), 0);

    const auto topdown_dfs = [&](const auto &self, const int p,
                                 const int u) -> void {
        down[u] = 1;
        parent[u] = p;
        for (const auto v : g[u]) {
            if (v == p) continue;
            self(self, u, v);
            down[u] *= down[v] + 1;
        }
    };
    topdown_dfs(topdown_dfs, 0, 0);

    vector<vector<mint>> pref(sz(g));
    vector<vector<mint>> suff(sz(g));

    for (int u = 0; u < sz(g); ++u) {
        pref[u].resize(sz(g[u]), 1);
        suff[u].resize(sz(g[u]), 1);

        for (int i = 0; i < sz(g[u]); ++i) {
            if (i == 0) {
                pref[u][i] = down[g[u][i]] + 1;
            } else {
                pref[u][i] = pref[u][i - 1] * (down[g[u][i]] + 1);
            }
        }

        for (int i = sz(g[u]) - 1; i >= 0; --i) {
            if (i == sz(g[u]) - 1) {
                suff[u][i] = down[g[u][i]] + 1;
            } else {
                suff[u][i] = suff[u][i + 1] * (down[g[u][i]] + 1);
            }
        }
    }

    vector<mint> up(sz(g), 1);
    queue<int> q;
    for (const auto v : g[0]) q.push(v);

    while (!empty(q)) {
        const auto u = q.front();
        q.pop();

        const auto p = parent[u];
        mint result{up[p]};
        for (const auto v : g[p]) {
            if (v == u || v == parent[p]) continue;
            result *= down[v] + 1;
        }
        ++result;
        up[u] = result;

        for (const auto v : g[u]) {
            if (v == parent[u]) continue;
            q.push(v);
        }
    }

    vector<mint> result(sz(g), 0);
    ranges::transform(down, up, begin(result),
                      [](const auto x, const auto y) { return x * y; });
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
