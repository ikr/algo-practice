#include <bits/stdc++.h>
using namespace std;

using pii = pair<int, int>;

static constexpr int INF = 1000 * 1000 * 1000;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

int max_candy(const vector<vector<int>> &G, const int T) {
    const auto start = sz(G) - 2;
    const auto goal = sz(G) - 1;
    if (G[start][goal] > T) return -1;

    const auto n = sz(G) - 2;
    vector<vector<int>> bits_by_pops(n + 1);
    for (int bits = 1; bits < (1 << n); ++bits) {
        bits_by_pops[__builtin_popcount(bits)].push_back(bits);
    }

    // D[i][j] is the length of the route beginning at the start, going through
    // all the candies corresponding to the bits set in j, and ending at candy i
    vector<vector<int>> D(n, vector(1 << n, INF));
    for (int u0{}; u0 < n; ++u0) D[u0][1 << u0] = G[start][u0];

    for (int p{1}; p <= n - 1; ++p) {
        for (const auto bits : bits_by_pops[p]) {
            for (int u{}; u < n; ++u) {
                if (D[u][bits] == INF) continue;

                for (int v{}; v < n; ++v) {
                    if ((1 << v) & bits) continue;
                    D[v][bits | (1 << v)] =
                        min(D[v][bits | (1 << v)], G[u][v] + D[u][bits]);
                }
            }
        }
    }

    int result{};
    for (int u{}; u < n; ++u) {
        for (int bits{1}; bits < (1 << n); ++bits) {
            if (D[u][bits] == INF) continue;
            if (D[u][bits] + G[u][goal] > T) continue;
            result = max(result, __builtin_popcount(bits));
        }
    }
    return result;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int H, W, T;
    cin >> H >> W >> T;

    vector<string> grid(H);
    for (auto &row : grid) {
        cin >> row;
        assert(sz(row) == W);
    }

    pii start{}, goal{};
    vector<pii> candies;

    for (int ro = 0; ro < H; ++ro) {
        for (int co = 0; co < W; ++co) {
            switch (grid[ro][co]) {
            case 'S':
                start = pii{ro, co};
                break;
            case 'G':
                goal = pii{ro, co};
                break;
            case 'o':
                candies.emplace_back(ro, co);
            }
        }
    }

    const auto n = sz(candies) + 2;
    vector<vector<int>> G(n, vector(n, INF));

    const auto vertex_roco = [&](const int v) -> pii {
        if (v == n - 2) return start;
        if (v == n - 1) return goal;
        assert(0 <= v && v < sz(candies));
        return candies[v];
    };

    const auto vertices_by_roco = [&]() {
        map<pii, int> result;
        for (int v = 0; v < n; ++v) result[vertex_roco(v)] = v;
        return result;
    }();

    const auto trace_from = [&](const int u0) -> void {
        vector<vector<int>> D(H, vector(W, INF));
        const auto [ro0, co0] = vertex_roco(u0);
        D[ro0][co0] = 0;

        queue<pii> q;
        q.push(vertex_roco(u0));

        while (!q.empty()) {
            const auto [ro, co] = q.front();
            q.pop();

            if (ro > 0 && grid[ro - 1][co] != '#' && D[ro - 1][co] == INF) {
                D[ro - 1][co] = D[ro][co] + 1;
                q.emplace(ro - 1, co);
            }

            if (co < W - 1 && grid[ro][co + 1] != '#' && D[ro][co + 1] == INF) {
                D[ro][co + 1] = D[ro][co] + 1;
                q.emplace(ro, co + 1);
            }

            if (ro < H - 1 && grid[ro + 1][co] != '#' && D[ro + 1][co] == INF) {
                D[ro + 1][co] = D[ro][co] + 1;
                q.emplace(ro + 1, co);
            }

            if (co > 0 && grid[ro][co - 1] != '#' && D[ro][co - 1] == INF) {
                D[ro][co - 1] = D[ro][co] + 1;
                q.emplace(ro, co - 1);
            }
        }

        for (int ro = 0; ro < H; ++ro) {
            for (int co = 0; co < W; ++co) {
                if (D[ro][co] == INF) continue;
                const auto it = vertices_by_roco.find({ro, co});
                if (it == cend(vertices_by_roco)) continue;

                G[u0][it->second] = D[ro][co];
            }
        }
    };

    for (int u0 = 0; u0 < n; ++u0) trace_from(u0);
    cout << max_candy(G, T) << '\n';
    return 0;
}
