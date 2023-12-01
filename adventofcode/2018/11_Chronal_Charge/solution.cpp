#include <bits/stdc++.h>
using namespace std;

using Coord = pair<int, int>;

constexpr int cell_power_level(const Coord xy, const int grid_serial_number) {
    const auto [x, y] = xy;
    const auto rack_id = x + 10;
    const auto a = (rack_id * y + grid_serial_number) * rack_id;
    const auto b = (a / 100) % 10;
    return b - 5;
}

int main() {
    const auto n = 300;
    int grid_serial_number;
    cin >> grid_serial_number;

    vector<vector<int>> grid(n, vector<int>(n, 0));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            grid[i][j] = cell_power_level({i + 1, j + 1}, grid_serial_number);
        }
    }

    auto ss = grid;
    for (int i = 1; i < n; ++i) {
        ss[i][0] += ss[i - 1][0];
        ss[0][i] += ss[0][i - 1];
    }

    for (int i = 1; i < n; ++i) {
        for (int j = 1; j < n; ++j) {
            ss[i][j] += ss[i - 1][j] + ss[i][j - 1] - ss[i - 1][j - 1];
        }
    }

    const auto square_sum = [&](const Coord left_top, const int d) -> int {
        const auto [x0, y0] = left_top;
        assert(0 <= x0 && x0 < n);
        assert(0 <= y0 && y0 < n);

        const auto x1 = x0 + d - 1;
        assert(0 <= x1 && x1 < n);
        const auto y1 = y0 + d - 1;
        assert(0 <= y1 && y1 < n);

        auto a = ss[x1][y1];
        if (y0) a -= ss[x1][y0 - 1];
        if (x0) a -= ss[x0 - 1][y1];
        if (x0 && y0) a += ss[x0 - 1][y0 - 1];
        return a;
    };

    int hi = INT_MIN;
    int left = -1;
    int top = -1;
    int side = -1;

    for (int d = 1; d <= n; ++d) {
        for (int i = 0; i + d <= n; ++i) {
            for (int j = 0; j + d <= n; ++j) {
                const auto candidate = square_sum({i, j}, d);
                if (candidate > hi) {
                    hi = candidate;
                    left = i + 1;
                    top = j + 1;
                    side = d;
                }
            }
        }
    }

    cout << left << ',' << top << ',' << side << '\n';
    return 0;
}
