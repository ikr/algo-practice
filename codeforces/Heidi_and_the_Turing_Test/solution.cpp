#include <bits/stdc++.h>

using namespace std;

using XY = pair<int, int>;

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

    int max_x = INT_MIN;
    int min_x = INT_MAX;

    for (const auto [x, cnt] : points_count_by_x) {
        if (cnt < 2) continue;
        if (x > max_x) max_x = x;
        if (x < min_x) min_x = x;
    }

    int max_y = INT_MIN;
    int min_y = INT_MAX;

    for (const auto [y, cnt] : points_count_by_y) {
        if (cnt < 2) continue;
        if (y > max_y) max_y = y;
        if (y < min_y) min_y = y;
    }

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
