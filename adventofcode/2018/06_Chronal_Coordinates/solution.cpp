#include <bits/stdc++.h>
using namespace std;

using Coord = pair<int, int>;

static constexpr int LIM = 10000;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

Coord parse_coord(const string &src) {
    const string sep{", "};
    const auto isep = src.find(sep);
    return {stoi(src.substr(0, isep)), stoi(src.substr(isep + sz(sep)))};
}

constexpr Coord rotate(const Coord xy) {
    const auto [x, y] = xy;
    return {x + y, x - y};
}

constexpr int manhattan_distance(const Coord a, const Coord b) {
    const auto [ax, ay] = a;
    const auto [bx, by] = b;
    return abs(ax - bx) + abs(ay - by);
}

int main() {
    vector<Coord> points;
    vector<Coord> rotated_points;

    for (string line; getline(cin, line);) {
        const auto xy = parse_coord(line);
        points.push_back(xy);
        rotated_points.push_back(rotate(xy));
    }

    const auto n = sz(rotated_points);

    vector<int> indices_sorted_by_x(n);
    iota(begin(indices_sorted_by_x), end(indices_sorted_by_x), 0);
    ranges::sort(indices_sorted_by_x, [&](const int i, const int j) {
        return rotated_points[i].first < rotated_points[j].first;
    });

    vector<int> indices_sorted_by_y(n);
    iota(begin(indices_sorted_by_y), end(indices_sorted_by_y), 0);
    ranges::sort(indices_sorted_by_y, [&](const int i, const int j) {
        return rotated_points[i].second < rotated_points[j].second;
    });

    const auto xs = array{points[indices_sorted_by_x[0]].first,
                          points[indices_sorted_by_x.back()].first,
                          points[indices_sorted_by_y[0]].first,
                          points[indices_sorted_by_y.back()].first};

    const auto ys = array{points[indices_sorted_by_x[0]].second,
                          points[indices_sorted_by_x.back()].second,
                          points[indices_sorted_by_y[0]].second,
                          points[indices_sorted_by_y.back()].second};

    const auto x_lo = *ranges::min_element(xs);
    const auto x_hi = *ranges::max_element(xs);
    const auto y_lo = *ranges::min_element(ys);
    const auto y_hi = *ranges::max_element(ys);

    const auto sum_of_distances = [&](const Coord xy) -> int {
        return accumulate(cbegin(points), cend(points), 0,
                          [xy](const int acc, const Coord p) {
                              return acc + manhattan_distance(xy, p);
                          });
    };

    map<Coord, int> sum_of_distances_by_xy;

    for (int x = x_lo; x <= x_hi; ++x) {
        for (int y = y_lo; y <= y_hi; ++y) {
            const auto sd = sum_of_distances(Coord{x, y});
            if (sd < LIM) sum_of_distances_by_xy[{x, y}] = sd;
        }
    }

    cout << sz(sum_of_distances_by_xy) << '\n';
    return 0;
}
