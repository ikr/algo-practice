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

bool four_plus_trail_exists(const vector<string> &grid) {
    const auto H = sz(grid);
    const auto W = sz(grid[0]);
    const auto roco0 = start_coord(grid);

    const auto in_bounds = [&](const pii roco) {
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
        }
    }
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
