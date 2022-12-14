#include <bits/stdc++.h>
using namespace std;

using Coord = pair<int, int>;
using Waypoints = vector<Coord>;
using Grid = vector<string>;

constexpr int X(const Coord c) { return c.first; }
constexpr int Y(const Coord c) { return c.second; }

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

template <typename T>
constexpr pair<T, T> operator+(const pair<T, T> a, const pair<T, T> b) {
    return {a.first + b.first, a.second + b.second};
}

vector<string> split(const string &delim_regex, const string &s) {
    regex r(delim_regex);
    return vector<string>(sregex_token_iterator(cbegin(s), cend(s), r, -1),
                          sregex_token_iterator{});
}

constexpr int step_from_to(const int a, const int b) {
    if (a == b) return 0;
    return a < b ? 1 : -1;
}

constexpr Coord step_from_to(const Coord a, const Coord b) {
    return {step_from_to(X(a), X(b)), step_from_to(Y(a), Y(b))};
}

Coord parse_coord(const string &src) {
    const auto parts = split(",", src);
    assert(sz(parts) == 2);
    return {stoi(parts[0]), stoi(parts[1])};
}

Coord dimensions(const vector<Waypoints> &wpss) {
    int x_max{};
    int y_max{};

    for (const auto &wps : wpss) {
        for (const auto &[x, y] : wps) {
            x_max = max(x_max, x);
            y_max = max(y_max, y);
        }
    }

    return {x_max, y_max};
}

pair<Grid, Coord> structural_grid(const vector<Waypoints> &wpss,
                                  const Coord src_) {
    const auto [x_max, y_max] = dimensions(wpss);
    Grid grid(y_max + 3, string(3 * x_max + 3, '.'));

    for (const auto &wps : wpss) {
        for (int i = 1; i < sz(wps); ++i) {
            const auto step = step_from_to(wps[i - 1], wps[i]);

            for (auto cur = wps[i - 1];; cur = cur + step) {
                grid[Y(cur)][x_max + X(cur) + 1] = '#';
                if (cur == wps[i]) break;
            }
        }
    }

    for (int x = 0; x <= 3 * x_max + 2; ++x) {
        grid[y_max + 2][x] = '#';
    }

    const Coord src{x_max + X(src_) + 1, Y(src_)};
    grid[Y(src)][X(src)] = '+';
    return {grid, src};
}

Coord simulate_one_unit_falling(const Grid &grid, const Coord &src) {
    const auto H = sz(grid);
    const auto W = sz(grid[0]);

    const auto in_bounds = [&](const Coord xy) -> bool {
        return 0 <= X(xy) && X(xy) < W && 0 <= Y(xy) && Y(xy) < H;
    };

    const auto at = [&](const Coord xy) -> char {
        assert(in_bounds(xy));
        return grid[Y(xy)][X(xy)];
    };

    const auto is_space = [&](const Coord xy) -> bool {
        return in_bounds(xy) && at(xy) == '.';
    };

    auto cur = src;
    for (;;) {
        const auto cur_ = [&]() -> Coord {
            for (const auto &d : vector<Coord>{{0, 1}, {-1, 1}, {1, 1}}) {
                if (is_space(cur + d)) {
                    return cur + d;
                }
            }

            return cur;
        }();

        if (cur_ == cur) break;
        cur = cur_;
    }
    return cur;
}

int simulation_steps_until_stable(const vector<Waypoints> &wpss,
                                  const Coord src_) {
    auto [grid, src] = structural_grid(wpss, src_);

    int result{};
    for (;;) {
        const auto xy = simulate_one_unit_falling(grid, src);
        grid[Y(xy)][X(xy)] = 'o';
        ++result;
        if (xy == src) break;
    }

    return result;
}

int main() {
    vector<Waypoints> wpss;

    for (string line; getline(cin, line);) {
        const auto point_sources = split(" -> ", line);
        Waypoints wps(sz(point_sources));
        transform(cbegin(point_sources), cend(point_sources), begin(wps),
                  parse_coord);
        wpss.push_back(wps);
    }

    cout << simulation_steps_until_stable(wpss, {500, 0}) << '\n';
    return 0;
}
