#include <atcoder/modint>
#include <bits/stdc++.h>
using namespace std;

using mint = atcoder::modint;
using pii = pair<int, int>;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

vector<mint> num_ways(const vector<vector<int>> &g) {
    vector<mint> in_subtree(sz(g), 0);
    vector<int> parent(sz(g), 0);

    const auto topdown_dfs = [&](const auto &self, const int p,
                                 const int u) -> void {
        in_subtree[u] = 1;
        parent[u] = p;
        for (const auto v : g[u]) {
            if (v == p) continue;
            self(self, u, v);
            in_subtree[u] *= in_subtree[v] + 1;
        }
    };
    topdown_dfs(topdown_dfs, 0, 0);

    vector<vector<mint>> pref(sz(g));
    vector<vector<mint>> suff(sz(g));

    for (int u = 0; u < sz(g); ++u) {
        pref[u].resize(sz(g[u]), 1);
        suff[u].resize(sz(g[u]), 1);

        for (int i = 0; i < sz(g[u]); ++i) {
            if (g[u][i] == parent[u]) {
                pref[u][i] = i ? pref[u][i - 1] : 1;
            } else if (i == 0) {
                pref[u][i] = in_subtree[g[u][i]] + 1;
            } else {
                pref[u][i] = pref[u][i - 1] * (in_subtree[g[u][i]] + 1);
            }
        }

        for (int i = sz(g[u]) - 1; i >= 0; --i) {
            if (g[u][i] == parent[u]) {
                suff[u][i] = (i == sz(g[u]) - 1) ? 1 : suff[u][i + 1];
            } else if (i == sz(g[u]) - 1) {
                suff[u][i] = in_subtree[g[u][i]] + 1;
            } else {
                suff[u][i] = suff[u][i + 1] * (in_subtree[g[u][i]] + 1);
            }
        }
    }

    vector<mint> out_of_subtree(sz(g), 1);
    queue<pii> q;
    for (int i = 0; i < sz(g[0]); ++i) q.emplace(i, g[0][i]);

    while (!empty(q)) {
        const auto [iu, u] = q.front();
        q.pop();

        const auto p = parent[u];
        mint result{out_of_subtree[p]};

        // for (const auto v : g[p]) {
        //     if (v == u || v == parent[p]) continue;
        //     result *= in_subtree[v] + 1;
        // }
        if (!empty(g[p])) {
            if (iu) result *= pref[p][iu - 1];
            if (iu != sz(g[p]) - 1) result *= suff[p][iu + 1];
        }

        ++result;
        out_of_subtree[u] = result;

        for (int i = 0; i < sz(g[u]); ++i) {
            const auto v = g[u][i];
            if (v == parent[u]) continue;
            q.emplace(i, v);
        }
    }

    vector<mint> result(sz(g), 0);
    ranges::transform(in_subtree, out_of_subtree, begin(result),
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
