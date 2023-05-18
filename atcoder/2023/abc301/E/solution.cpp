#include <bits/stdc++.h>
using namespace std;

using pii = pair<int, int>;

static constexpr int INF = 1000 * 1000 * 1000;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

vector<int> indices_of_ones(const int bits) {
    vector<int> result;
    for (int i = 0; i < 20; ++i) {
        if ((1 << i) & bits) result.push_back(i);
    }
    return result;
}

int solve_tsp(const vector<vector<int>> &D, const vector<int> &sites) {
    const auto m = sz(sites);
    vector<vector<int>> memo(m, vector(1 << m, -1));

    const auto goal = sz(D) - 1;
    // We're on site index u, with av_bits indicating which other site indices
    // are open for a visit. The returned total distance includes the sites
    // tour, and the path from the last site to the goal.
    const auto recur = [&](const auto self, const int u,
                           const int av_bits) -> int {
        if (memo[u][av_bits] != -1) return memo[u][av_bits];

        return memo[u][av_bits] = [&]() -> int {
            assert(((1 << u) & av_bits) == 0);
            if (av_bits == 0) return D[sites[u]][goal];

            int result{INF};
            for (const auto v : indices_of_ones(av_bits)) {
                if (D[sites[u]][sites[v]] == INF) return INF;

                const auto sub = self(self, v, av_bits ^ (1 << v));
                if (sub == INF) return INF;

                result = min(result, D[sites[u]][sites[v]] + sub);
            }
            return result;
        }();
    };

    const auto start = sz(D) - 2;
    const int av_bits_all = (1 << m) - 1;
    int result{INF};

    for (int u0 = 0; u0 < m; ++u0) {
        if (D[start][sites[u0]] == INF) return INF;

        const auto tail = recur(recur, u0, av_bits_all ^ (1 << u0));
        if (tail == INF) return INF;

        result = min(result, D[start][sites[u0]] + tail);
    }

    return result;
}

int max_candy(const vector<vector<int>> &D, const int T) {
    const auto start = sz(D) - 2;
    const auto goal = sz(D) - 1;
    if (D[start][goal] > T) return -1;

    const auto n = sz(D) - 2;

    int lo = 0;
    int hi = n;
    if (solve_tsp(D, indices_of_ones((1 << n) - 1)) <= T) return hi;

    vector<vector<int>> bits_by_pops(n + 1);
    for (int bits = 1; bits < (1 << n); ++bits) {
        bits_by_pops[__builtin_popcount(bits)].push_back(bits);
    }

    const auto doable = [&](const int pops) -> bool {
        for (const auto bits : bits_by_pops[pops]) {
            if (solve_tsp(D, indices_of_ones(bits)) <= T) return true;
        }
        return false;
    };

    while (lo + 1 < hi) {
        const auto mid = lo + (hi - lo) / 2;
        if (doable(mid)) {
            lo = mid;
        } else {
            hi = mid;
        }
    }

    return lo;
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
