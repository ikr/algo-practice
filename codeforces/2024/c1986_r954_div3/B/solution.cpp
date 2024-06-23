#include <bits/stdc++.h>
using namespace std;

using pii = pair<int, int>;
using tri = tuple<int, int, int>;

template <typename T1, typename T2>
ostream &operator<<(ostream &os, const pair<T1, T2> &x) {
    os << '(' << x.first << ' ' << x.second << ')';
    return os;
}

template <typename T> ostream &operator<<(ostream &os, const vector<T> &xs) {
    for (auto i = xs.cbegin(); i != xs.cend(); ++i) {
        if (i != xs.cbegin()) os << ' ';
        os << *i;
    }
    return os;
}

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

pair<vector<vector<int>>, vector<vector<int>>>
domination_graphs(const vector<vector<int>> &grid) {
    const auto H = sz(grid);
    const auto W = sz(grid[0]);

    const auto code = [W](const int r, const int c) -> int {
        return r * W + c;
    };

    const auto in_bounds = [&](const int r, const int c) -> bool {
        return 0 <= r && r < H && 0 <= c && c < W;
    };

    const auto adjacent_coords = [&](const int r0,
                                     const int c0) -> vector<pii> {
        vector<pii> adj;
        for (const auto &rc : vector<pii>{
                 {r0 - 1, c0}, {r0, c0 + 1}, {r0 + 1, c0}, {r0, c0 - 1}}) {
            if (in_bounds(rc.first, rc.second)) adj.push_back(rc);
        }
        return adj;
    };

    const auto dominates = [&](const int r0, const int c0) -> bool {
        const auto adj = adjacent_coords(r0, c0);
        return all_of(cbegin(adj), cend(adj), [&](const auto rc) {
            const auto [r, c] = rc;
            return grid[r0][c0] > grid[r][c];
        });
    };

    vector<vector<int>> g(H * W);
    vector<vector<int>> g_(H * W);
    for (int r0 = 0; r0 < H; ++r0) {
        for (int c0 = 0; c0 < W; ++c0) {
            if (dominates(r0, c0)) {
                for (const auto &[r, c] : adjacent_coords(r0, c0)) {
                    const auto u = code(r0, c0);
                    const auto v = code(r, c);
                    g[u].push_back(v);
                    g_[v].push_back(u);
                }
            }
        }
    }
    return {g, g_};
}

vector<int> out_degrees(const vector<vector<int>> &g) {
    const auto n = sz(g);
    vector<int> result(n, 0);
    for (int u = 0; u < n; ++u) {
        result[u] = sz(g[u]);
    }
    return result;
}

vector<vector<int>> result_matrix(vector<vector<int>> grid) {
    const auto H = sz(grid);
    const auto W = sz(grid[0]);
    const auto coord = [W](const auto cd) -> pii { return {cd / W, cd % W}; };

    const auto [g, g_] = domination_graphs(grid);
    auto deg = out_degrees(g);
    const auto n = sz(deg);

    set<int> todo;
    for (int u = 0; u < n; ++u) {
        if (!empty(g[u])) todo.insert(u);
    }
    if (empty(todo)) return grid;

    priority_queue<tri> q;
    for (int v = 0; v < n; ++v) {
        if (deg[v] == 0) {
            const auto [r, c] = coord(v);
            q.emplace(-r, -c, v);
        };
    }

    vector<int> seq;
    seq.reserve(n);

    while (!empty(q)) {
        const auto [_a, _b, v] = q.top();
        q.pop();
        seq.push_back(v);

        for (const auto u : g_[v]) {
            --deg[u];
            if (deg[u] == 0) {
                const auto [r, c] = coord(u);
                q.emplace(-r, -c, u);
            }
        }
    }
    assert(sz(seq) == n);

    const auto in_bounds = [&](const int r, const int c) -> bool {
        return 0 <= r && r < H && 0 <= c && c < W;
    };

    const auto adjacent_coords = [&](const int r0,
                                     const int c0) -> vector<pii> {
        vector<pii> adj;
        for (const auto &rc : vector<pii>{
                 {r0 - 1, c0}, {r0, c0 + 1}, {r0 + 1, c0}, {r0, c0 - 1}}) {
            if (in_bounds(rc.first, rc.second)) adj.push_back(rc);
        }
        return adj;
    };

    for (const auto u : seq) {
        const auto [r0, c0] = coord(u);
        if (todo.contains(u)) {
            int val = grid[r0][c0];
            for (const auto &[r, c] : adjacent_coords(r0, c0)) {
                val = min(val, grid[r][c]);
            }
            grid[r0][c0] = val;
        }
    }
    return grid;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t;
    cin >> t;
    while (t--) {
        int H, W;
        cin >> H >> W;
        vector<vector<int>> grid(H, vector(W, 0));
        for (auto &row : grid) {
            for (auto &x : row) cin >> x;
        }

        for (const auto &row : result_matrix(std::move(grid))) {
            cout << row << '\n';
        }
    }

    return 0;
}
