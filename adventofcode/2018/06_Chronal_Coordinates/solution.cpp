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

constexpr int chebyshev_distance(const Coord a, const Coord b) {
    const auto [ax, ay] = a;
    const auto [bx, by] = b;
    return max(abs(ax - bx), abs(ay - by));
}

template <typename T> int index_of(const vector<T> &xs, const T x) {
    const auto it = find(cbegin(xs), cend(xs), x);
    assert(it != cend(xs));
    return inof(it - cbegin(xs));
}

int main() {
    vector<Coord> points;

    for (string line; getline(cin, line);) {
        points.push_back(rotate(parse_coord(line)));
    }

    const auto n = sz(points);

    vector<int> indices_sorted_by_x(n);
    iota(begin(indices_sorted_by_x), end(indices_sorted_by_x), 0);
    ranges::sort(indices_sorted_by_x, [&](const int i, const int j) {
        return points[i].first < points[j].first;
    });

    vector<int> indices_sorted_by_y(n);
    iota(begin(indices_sorted_by_y), end(indices_sorted_by_y), 0);
    ranges::sort(indices_sorted_by_y, [&](const int i, const int j) {
        return points[i].second < points[j].second;
    });

    int hi{};

    for (int i = 0; i < n; ++i) {
        const auto j = index_of(indices_sorted_by_x, i);
        const auto k = index_of(indices_sorted_by_y, i);

        if (0 < j && j < n - 1 && 0 < k && k < n - 1) {
            cerr << "Point " << i << " is internal" << endl;
        }
    }

    return 0;
}
