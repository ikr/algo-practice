#include <bits/stdc++.h>
using namespace std;

using Coord = pair<int, int>;

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

template <typename T> int index_of(const vector<T> &xs, const T x) {
    const auto it = find(cbegin(xs), cend(xs), x);
    assert(it != cend(xs));
    return inof(it - cbegin(xs));
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

    const auto x_lo = rotated_points[indices_sorted_by_x[0]].first;
    const auto x_hi = rotated_points[indices_sorted_by_x.back()].first;
    const auto y_lo = rotated_points[indices_sorted_by_y[0]].second;
    const auto y_hi = rotated_points[indices_sorted_by_y.back()].second;

    for (int i = 0; i < n; ++i) {
        const auto j = index_of(indices_sorted_by_x, i);
        if (j == 0 || j == n - 1) continue;
        const auto k = index_of(indices_sorted_by_y, i);
        if (k == 0 || k == n - 1) continue;
    }

    return 0;
}
