#include <bits/stdc++.h>
using namespace std;

using Coord = pair<int, int>;

template <typename T>
constexpr pair<T, T> operator+(const pair<T, T> a, const pair<T, T> b) {
    return {a.first + b.first, a.second + b.second};
}

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

static const unordered_map<char, vector<Coord>> ConnectionDeltas{
    {'|', {{-1, 0}, {1, 0}}}, {'-', {{0, -1}, {0, 1}}},
    {'L', {{-1, 0}, {0, 1}}}, {'J', {{-1, 0}, {0, -1}}},
    {'7', {{1, 0}, {0, -1}}}, {'F', {{1, 0}, {0, 1}}}};

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

Coord start_coord(const vector<string> &grid) {
    for (int ro = 0; ro < sz(grid); ++ro) {
        for (int co = 0; co < sz(grid[ro]); ++co) {
            if (grid[ro][co] == 'S') return {ro, co};
        }
    }

    assert(false && "Start missing");
    return {-1, -1};
}

int main() {
    vector<string> grid;
    for (string s; getline(cin, s);) grid.emplace_back(std::move(s));

    const auto H = sz(grid);
    const auto W = sz(grid[0]);

    const auto in_bounds = [H, W](const Coord u) {
        const auto [ro, co] = u;
        return 0 <= ro && ro < H && 0 <= co && co < W;
    };

    const auto cell = [&](const Coord u) {
        return in_bounds(u) ? grid[u.first][u.second] : ' ';
    };

    const auto adjacent = [&](const Coord u) -> vector<Coord> {
        const auto c = cell(u);
        assert(c != 'S');
        if (!ConnectionDeltas.contains(c)) return {};

        vector<Coord> result;
        for (const auto &d : ConnectionDeltas.at(c)) {
            const auto v = u + d;
            if (in_bounds(v)) result.push_back(v);
        }
        return result;
    };

    const auto is_connected = [&](const Coord u, const Coord delta) -> bool {
        for (const auto &v : adjacent(u + delta)) {
            if (v == u) return true;
        }
        return false;
    };

    return 0;
}
