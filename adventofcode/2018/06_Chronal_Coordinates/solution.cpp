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

    const auto is_edge_point = [&](const int i) {
        return i == indices_sorted_by_x[0] || i == indices_sorted_by_x.back() ||
               i == indices_sorted_by_y[0] || i == indices_sorted_by_y.back();
    };

    const auto closest_point_index = [&](const Coord xy) -> optional<int> {
        multimap<int, int> center_indices_by_distance;

        for (int i = 0; i < n; ++i) {
            const auto d = manhattan_distance(xy, points[i]);
            center_indices_by_distance.emplace(d, i);
        }

        assert(!empty(center_indices_by_distance));
        const auto [d, i] = *cbegin(center_indices_by_distance);
        if (center_indices_by_distance.count(d) > 1) return nullopt;
        return is_edge_point(i) ? nullopt : optional{i};
    };

    map<Coord, int> centers;

    for (int x = x_lo; x <= x_hi; ++x) {
        for (int y = y_lo; y <= y_hi; ++y) {
            const auto i = closest_point_index({x, y});
            if (!i) continue;
            centers.emplace(Coord{x, y}, *i);
        }
    }

    vector<int> freq(n, 0);
    for (const auto &[_, i] : centers) ++freq[i];

    cout << *ranges::max_element(freq) << '\n';
    return 0;
}
