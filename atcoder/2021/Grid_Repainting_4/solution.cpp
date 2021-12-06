#include <bits/stdc++.h>
using namespace std;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

using Coord = complex<int>;
constexpr int row(const Coord coord) { return coord.real(); }
constexpr int col(const Coord coord) { return coord.imag(); }

struct CoordLess final {
    bool operator()(const Coord &a, const Coord &b) const {
        return (row(a) == row(b)) ? (col(a) < col(b)) : (row(a) < row(b));
    }
};

static const vector<Coord> DELTAS{{-1, 0}, {0, 1}, {1, 0}, {0, -1}};

constexpr bool in_bounds(const Coord dim, const Coord p) {
    const int H = row(dim);
    const int W = col(dim);
    return 0 <= row(p) && row(p) < H && 0 <= col(p) && col(p) < W;
}

char suggest_color(const vector<string> &grid, const Coord p) {
    assert(grid[row(p)][col(p)] == '.');
    set<char> av{'1', '2', '3', '4', '5'};

    for (const auto d : DELTAS) {
        const auto p_ = p + d;

        if (in_bounds({sz(grid), sz(grid[0])}, p_)) {
            av.erase(grid[row(p_)][col(p_)]);
        }
    }

    assert(!av.empty());
    return *cbegin(av);
}

set<Coord, CoordLess> initial_queue(const vector<string> &grid) {
    const int H = sz(grid);
    const int W = sz(grid[0]);
    set<Coord, CoordLess> result;

    for (int ro = 0; ro < H; ++ro) {
        for (int co = 0; co < W; ++co) {
            if (grid[ro][co] != '.') {
                const Coord p{ro, co};

                for (const auto d : DELTAS) {
                    const auto p_ = p + d;

                    if (in_bounds({sz(grid), sz(grid[0])}, p_) &&
                        grid[row(p_)][col(p_)] == '.') {
                        result.insert(p_);
                    }
                }
            }
        }
    }

    return result;
}

void paint_all(vector<string> &grid) {
    auto q = initial_queue(grid);
    if (q.empty()) {
        q.emplace(0, 0);
    }

    while (!q.empty()) {
        const auto p = *cbegin(q);
        q.erase(cbegin(q));

        grid[row(p)][col(p)] = suggest_color(grid, p);
        for (const auto d : DELTAS) {
            const auto p_ = p + d;

            if (in_bounds({sz(grid), sz(grid[0])}, p_) &&
                grid[row(p_)][col(p_)] == '.') {
                q.insert(p_);
            }
        }
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int H, W;
    cin >> H >> W;

    vector<string> grid(H, string(W, ' '));
    for (auto &row : grid) {
        cin >> row;
    }

    paint_all(grid);
    for (const auto &row : grid) {
        cout << row << '\n';
    }
    return 0;
}
