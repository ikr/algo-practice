#include <bits/stdc++.h>
using namespace std;

using Coord = pair<int, int>;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

int cell_power_level(const Coord xy, const int grid_serial_number) {
    const auto [x, y] = xy;
    const auto rack_id = x + 10;
    const auto a = (rack_id * y + grid_serial_number) * rack_id;
    const auto b = (a / 100) % 10;
    return b - 5;
}

int main() {
    int grid_serial_number;
    cin >> grid_serial_number;

    vector<vector<int>> grid(300, vector<int>(300, 0));
    for (int i = 0; i < sz(grid); ++i) {
        for (int j = 0; j < sz(grid[i]); ++j) {
            grid[i][j] = cell_power_level({i + 1, j + 1}, grid_serial_number);
        }
    }

    const auto box_power = [&](const Coord top_left) -> int {
        const auto [i0, j0] = top_left;
        int result{};

        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                result += grid[i0 + i][j0 + j];
            }
        }

        return result;
    };

    int hi{INT_MIN};
    Coord ans{0, 0};
    for (int i = 0; i < sz(grid) - 2; ++i) {
        for (int j = 0; j < sz(grid[i]) - 2; ++j) {
            const auto bp = box_power({i, j});
            if (bp > hi) {
                hi = bp;
                ans = {i + 1, j + 1};
            }
        }
    }
    cout << hi << ' ' << ans.first << ',' << ans.second << '\n';
    return 0;
}
