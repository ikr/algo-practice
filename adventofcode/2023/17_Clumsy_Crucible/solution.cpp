#include <bits/stdc++.h>
using namespace std;

template <typename T1, typename T2>
ostream &operator<<(ostream &os, const pair<T1, T2> &x) {
    os << '(' << x.first << ' ' << x.second << ')';
    return os;
}

template <typename T> ostream &operator<<(ostream &os, const vector<T> &xs) {
    os << '[';
    for (auto i = xs.cbegin(); i != xs.cend(); ++i) {
        if (i != xs.cbegin()) os << ' ';
        os << *i;
    }
    os << ']';
    return os;
}

using Coord = pair<int, int>;

static constexpr array Delta{Coord{-1, 0}, Coord{0, 1}, Coord{1, 0},
                             Coord{0, -1}};

template <typename T>
ostream &operator<<(ostream &os, const vector<vector<T>> &xss) {
    for (const auto &xs : xss) os << xs << '\n';
    return os;
}

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

template <typename T>
constexpr pair<T, T> operator+(const pair<T, T> a, const pair<T, T> b) {
    return {a.first + b.first, a.second + b.second};
}

template <typename T>
constexpr pair<T, T> scaled_by(const pair<T, T> ab, const T k) {
    return {k * ab.first, k * ab.second};
}

int main() {
    vector<string> grid;
    for (string line; getline(cin, line);) {
        grid.push_back(std::move(line));
    }

    const int H = sz(grid);
    const int W = sz(grid[0]);

    const auto in_bounds = [&](const Coord rc) -> bool {
        const auto [r, c] = rc;
        return 0 <= r && r < H && 0 <= c && c < W;
    };

    const auto heat_loss_at = [&](const Coord rc) -> int {
        assert(in_bounds(rc));
        const auto [r, c] = rc;
        return grid[r][c] - '0';
    };

    const auto adjacent_coord_losses =
        [&](const Coord rc) -> vector<pair<Coord, int>> {
        vector<pair<Coord, int>> result;

        for (const auto &delta : Delta) {
            int current_heat_loss{};

            for (int steps = 1; steps <= 3; ++steps) {
                const auto shift = scaled_by(delta, steps);
                if (!in_bounds(rc + shift)) break;
                current_heat_loss += heat_loss_at(rc + shift);
                result.emplace_back(rc + shift, current_heat_loss);
            }
        }

        return result;
    };

    cerr << adjacent_coord_losses({0, 0}) << endl;
    return 0;
}
