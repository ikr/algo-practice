#include <bits/stdc++.h>
using namespace std;

using vi = vector<int>;
using vvi = vector<vi>;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

using Coord = complex<int>;
constexpr int row(const Coord coord) { return coord.real(); }
constexpr int col(const Coord coord) { return coord.imag(); }

using PrioCoord = pair<int, Coord>;

struct pq_greater final {
    bool operator()(const PrioCoord &a, const PrioCoord &b) const {
        return a.first > b.first;
    }
};

using PrioQueue = priority_queue<PrioCoord, vector<PrioCoord>, pq_greater>;

constexpr bool in_bounds(const int H, const int W, const Coord coord) {
    return (0 <= row(coord) && row(coord) < H && 0 <= col(coord) &&
            col(coord) < W);
}

vector<Coord> adjacent(const int H, const int W, const Coord coord) {
    static const vector<Coord> deltas{{-1, 0}, {0, 1}, {1, 0}, {0, -1}};
    vector<Coord> ans;

    for (const auto delta : deltas) {
        const auto x = coord + delta;
        if (in_bounds(H, W, x)) ans.push_back(x);
    }

    return ans;
}

pair<PrioQueue, vector<vector<bool>>> init_queue(const vvi &grid) {
    const int H = sz(grid);
    const int W = sz(grid[0]);
    vector<vector<bool>> discovered(H, vector<bool>(W, false));

    PrioQueue q;

    for (int ro = 0; ro < H; ++ro) {
        q.emplace(grid[ro][0], Coord{ro, 0});
        discovered[ro][0] = true;

        q.emplace(grid[ro][W - 1], Coord{ro, W - 1});
        discovered[ro][W - 1] = true;
    }

    for (int co = 0; co < W; ++co) {
        q.emplace(grid[0][co], Coord{0, co});
        discovered[0][co] = true;

        q.emplace(grid[H - 1][co], Coord{H - 1, co});
        discovered[H - 1][co] = true;
    }

    return {q, discovered};
}

int solve(const vvi &grid) {
    const int H = sz(grid);
    const int W = sz(grid[0]);
    auto [q, discovered] = init_queue(grid);
    int ans = 0;
    int edge_level = -1;

    while (!q.empty()) {
        const auto [h, u] = q.top();
        q.pop();
        edge_level = max(edge_level, h);

        for (const auto v : adjacent(H, W, u)) {
            if (discovered[row(v)][col(v)]) continue;
            discovered[row(v)][col(v)] = true;

            if (grid[row(v)][col(v)] < edge_level) {
                ans += edge_level - grid[row(v)][col(v)];
                q.emplace(edge_level, v);
            } else {
                q.emplace(grid[row(v)][col(v)], v);
            }
        }
    }

    return ans;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int T;
    cin >> T;
    for (int i = 1; i <= T; ++i) {
        int R, C;
        cin >> R >> C;
        vvi grid(R, vi(C, 0));

        for (auto &row : grid) {
            for (auto &x : row) cin >> x;
        }

        cout << "Case #" << i << ": " << solve(grid) << '\n';
    }

    return 0;
}
