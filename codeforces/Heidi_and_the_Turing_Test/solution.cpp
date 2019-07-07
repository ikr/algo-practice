#include <bits/stdc++.h>

using namespace std;

using XY = pair<int, int>;

pair<int, int>
minmax_coord_with_count_of_at_least_two(const map<int, int> &count_by_coord) {
    int max_c = INT_MIN;
    int min_c = INT_MAX;

    for (const auto [c, cnt] : count_by_coord) {
        if (cnt < 2) continue;
        if (c > max_c) max_c = c;
        if (c < min_c) min_c = c;
    }

    return {min_c, max_c};
}

int main() {
    int min_count_per_side;
    cin >> min_count_per_side;

    const auto sz = 4 * min_count_per_side + 1;

    vector<XY> ps(sz);
    for (auto &p : ps) cin >> p.first >> p.second;

    map<int, int> points_count_by_x;
    map<int, int> points_count_by_y;

    for (const auto [x, y] : ps) {
        ++points_count_by_x[x];
        ++points_count_by_y[y];
    }

    const auto [min_x, max_x] =
        minmax_coord_with_count_of_at_least_two(points_count_by_x);

    const auto [min_y, max_y] =
        minmax_coord_with_count_of_at_least_two(points_count_by_y);

    for (const auto [x, y] : ps) {
        const bool on_the_square =
            ((x == min_x || x == max_x) && min_y <= y && y <= max_y) ||
            ((y == min_y || y == max_y) && min_x <= x && x <= max_x);

        if (!on_the_square) {
            cout << x << ' ' << y << '\n';
            break;
        }
    }
}
