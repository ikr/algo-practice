#include <bits/stdc++.h>
using namespace std;

using pii = pair<int, int>;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

int neighs(const vector<string> &grid, const pii roco) {
    const auto H = sz(grid);
    const auto W = sz(grid[0]);
    const auto [ro, co] = roco;

    int result{};
    result += (ro > 0 && grid[ro - 1][co] == '^');
    result += (ro < H - 1 && grid[ro + 1][co] == '^');
    result += (co > 0 && grid[ro][co - 1] == '^');
    result += (co < W - 1 && grid[ro][co + 1] == '^');
    return result;
}

set<pii> unhappy_trees(const vector<string> &grid) {
    const auto H = sz(grid);
    const auto W = sz(grid[0]);
    set<pii> result;

    for (int ro = 0; ro < H; ++ro) {
        for (int co = 0; co < W; ++co) {
            if (neighs(grid, {ro, co}) < 2) result.emplace(ro, co);
        }
    }

    return result;
}

optional<vector<pii>> happiness_path(const vector<string> &grid,
                                     const set<pii> &uts,
                                     const vector<vector<bool>> &closed,
                                     const pii src) {
    const auto H = sz(grid);
    const auto W = sz(grid[0]);

    const auto in_bounds = [&](const pii roco) -> bool {
        const auto [ro, co] = roco;
        return 0 <= ro && ro < H && 0 <= co && co < W;
    };

    map<pii, pii> pre;
    queue<pii> q;
    set<pii> visited;
    q.push(src);
    visited.insert(src);

    optional<pii> dst;

    while (!q.empty()) {
        const auto [ro, co] = q.front();
        q.pop();

        for (const auto adj : {pii{ro - 1, co}, pii{ro, co + 1},
                               pii{ro + 1, co}, pii{ro, co - 1}}) {
            if (!in_bounds(adj)) continue;

            const auto [aro, aco] = adj;
            if (grid[aro][aco] == '#' || visited.count(adj)) {
                continue;
            }

            pre[adj] = pii{ro, co};
            if (uts.contains(adj)) {
                dst = adj;
                q = queue<pii>{};
                break;
            }

            visited.emplace(aro, aco);
            if (!closed[aro][aco]) q.emplace(aro, aco);
        }
    }

    if (!dst) return nullopt;

    vector<pii> result{*dst};
    result.reserve(sz(pre) + 1);

    auto u = *dst;
    while (pre.count(u)) {
        result.push_back(pre.at(u));
        u = pre.at(u);
    }

    reverse(begin(result), end(result));
    return result;
}

optional<vector<string>> perfect_garden(vector<string> grid) {
    const auto H = sz(grid);
    const auto W = sz(grid[0]);
    vector<vector<bool>> closed(H, vector(W, false));
    auto uts = unhappy_trees(grid);

    while (!uts.empty()) {
        const auto [ro0, co0] = *cbegin(uts);
        uts.erase(cbegin(uts));
    }

    return grid;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t;
    cin >> t;
    for (int i = 1; i <= t; ++i) {
        int H, W;
        cin >> H >> W;

        vector<string> grid(H);
        for (auto &row : grid) {
            cin >> row;
            assert(sz(row) == W);
        }

        const auto result = perfect_garden(move(grid));
        cout << "Case #" << i << ": " << (result ? "Possible" : "Impossible")
             << '\n';

        if (result) {
            for (const auto &row : *result) {
                cout << row << '\n';
            }
        }
    }

    return 0;
}
