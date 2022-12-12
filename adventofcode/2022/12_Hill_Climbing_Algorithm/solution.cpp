#include <bits/stdc++.h>
using namespace std;

using pii = pair<int, int>;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

pair<pii, pii> start_and_finish(const vector<string> &grid) {
    const auto H = sz(grid);
    const auto W = sz(grid[0]);
    pii start{-1, -1};
    pii finish{-1, -1};

    for (int ro = 0; ro < H; ++ro) {
        for (int co = 0; co < W; ++co) {
            if (grid[ro][co] == 'S') {
                start = pii{ro, co};
            } else if (grid[ro][co] == 'E') {
                finish = pii{ro, co};
            }
        }
    }

    return {start, finish};
}

constexpr int climb(const char src, const char dst) {
    return inof(dst) - inof(src);
}

template <typename T>
constexpr pair<T, T> operator+(const pair<T, T> a, const pair<T, T> b) {
    return {a.first + b.first, a.second + b.second};
}

int min_steps(vector<string> grid) {
    const auto [start, finish] = start_and_finish(grid);
    grid[start.first][start.second] = 'a';
    grid[finish.first][finish.second] = 'z';

    const auto H = sz(grid);
    const auto W = sz(grid[0]);

    const auto in_bounds = [&](const pii roco) -> bool {
        const auto [ro, co] = roco;
        return 0 <= ro && ro < H && 0 <= co && co < W;
    };

    const auto neighs = [&](const pii u) -> vector<pii> {
        vector<pii> result;

        for (const auto &delta :
             {pii{-1, 0}, pii{0, 1}, pii{1, 0}, pii{0, -1}}) {
            if (in_bounds(u + delta)) {
                result.push_back(u + delta);
            }
        }

        return result;
    };

    vector<vector<int>> D(H, vector(W, -1));
    D[start.first][start.second] = 0;

    queue<pii> q;
    q.push(start);

    while (!q.empty()) {
        const auto u = q.front();
        q.pop();

        for (const auto &v : neighs(u)) {
            if (D[v.first][v.second] >= 0 ||
                climb(grid[u.first][u.second], grid[v.first][v.second]) > 1) {
                continue;
            }

            D[v.first][v.second] = D[u.first][u.second] + 1;
            q.push(v);
        }
    }

    return D[finish.first][finish.second];
}

int main() {
    vector<string> grid;
    for (string line; getline(cin, line);) {
        grid.push_back(line);
    }

    cout << min_steps(move(grid)) << '\n';
    return 0;
}
