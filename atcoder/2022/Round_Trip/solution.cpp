#include <bits/stdc++.h>
using namespace std;

using pii = pair<int, int>;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

pii start_coord(const vector<string> &grid) {
    const auto H = sz(grid);
    const auto W = sz(grid[0]);

    for (int ro = 0; ro < H; ++ro) {
        for (int co = 0; co < W; ++co) {
            if (grid[ro][co] == 'S') return {ro, co};
        }
    }

    assert(false && "start_coord");
    return {-1, -1};
}

bool has_a_trivial_path(const vector<string> &g, const pii &roco) {
    const auto H = sz(g);
    const auto W = sz(g[0]);

    const auto in_bounds = [&](const pii &x) -> bool {
        const auto [ro, co] = x;
        return 0 <= ro && ro < H && 0 <= co && co < W;
    };

    const auto at = [&](const int ro, const int co) -> char {
        return in_bounds({ro, co}) ? g[ro][co] : '#';
    };

    const auto [ro, co] = roco;

    if (at(ro, co - 1) == '.' && at(ro - 1, co - 1) == '.' &&
        at(ro - 1, co) == '.') {
        return true;
    }

    if (at(ro - 1, co) == '.' && at(ro - 1, co + 1) == '.' &&
        at(ro, co + 1) == '.') {
        return true;
    }

    if (at(ro, co + 1) == '.' && at(ro + 1, co + 1) == '.' &&
        at(ro + 1, co) == '.') {
        return true;
    }

    if (at(ro + 1, co) == '.' && at(ro + 1, co - 1) == '.' &&
        at(ro, co - 1) == '.') {
        return true;
    }

    return false;
}

bool is_navigable(const vector<string> &grid, const pii &src, const pii &dst) {
    const auto H = sz(grid);
    const auto W = sz(grid[0]);

    const auto in_bounds = [&](const pii &roco) -> bool {
        const auto [ro, co] = roco;
        return 0 <= ro && ro < H && 0 <= co && co < W;
    };

    vector<vector<bool>> done(H, vector(W, false));
    done[src.first][src.second] = true;

    queue<pii> q;
    q.push(src);

    while (!q.empty()) {
        const auto [ro, co] = q.front();
        q.pop();

        for (const auto &v : {pii{ro - 1, co}, pii{ro, co + 1}, pii{ro + 1, co},
                              pii{ro, co - 1}}) {
            if (!in_bounds(v)) continue;
            const auto [ro_, co_] = v;
            if (grid[ro_][co_] != '.') continue;

            if (done[ro_][co_]) continue;
            if (v == dst) return true;

            done[ro_][co_] = true;
            q.emplace(ro_, co_);
        }
    }

    return false;
}

bool four_plus_trail_exists(const vector<string> &grid) {
    const auto H = sz(grid);
    const auto W = sz(grid[0]);
    const auto roco0 = start_coord(grid);

    if (has_a_trivial_path(grid, roco0)) return true;

    const auto in_bounds = [&](const pii &roco) -> bool {
        const auto [ro, co] = roco;
        return 0 <= ro && ro < H && 0 <= co && co < W;
    };

    vector<vector<int>> D(H, vector(W, -1));
    D[roco0.first][roco0.second] = 0;

    queue<pii> q;
    q.push(roco0);

    while (!q.empty()) {
        const auto [ro, co] = q.front();
        q.pop();

        for (const auto &v : {pii{ro - 1, co}, pii{ro, co + 1}, pii{ro + 1, co},
                              pii{ro, co - 1}}) {
            if (!in_bounds(v)) continue;
            const auto [ro_, co_] = v;
            if (grid[ro_][co_] == '#') continue;

            if (grid[ro_][co_] == 'S' && D[ro][co] >= 3) return true;
            if (D[ro_][co_] != -1) continue;

            D[ro_][co_] = D[ro][co] + 1;
            q.emplace(ro_, co_);
        }
    }

    return false;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int H, W;
    cin >> H >> W;

    vector<string> grid(H);
    for (auto &row : grid) cin >> row;

    cout << (four_plus_trail_exists(grid) ? "Yes" : "No") << '\n';
    return 0;
}
