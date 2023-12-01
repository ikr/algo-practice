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

    cerr << cell_power_level({101, 153}, 71) << endl;
    return 0;
}
