#include <cassert>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

int first_above_row(const vector<string> &grid, const int b, const int co) {
    for (int ro = b - 1; ro >= 0; --ro) {
        if (grid[ro][co] == '*') return ro;
    }
    return -1;
}

int fall_down(vector<string> &grid, const int ro, const int co) {
    const int H = sz(grid);
    assert(grid[ro][co] == '*');

    int dest = ro;
    while (dest < H - 1 && grid[dest + 1][co] == '.') ++dest;
    grid[ro][co] = '.';
    grid[dest][co] = '*';
    return dest;
}

void simulate_column(vector<string> &grid, const int co) {
    const int H = sz(grid);
    int b = H;

    for (;;) {
        const auto ro = first_above_row(grid, b, co);
        if (ro < 0) break;
        b = fall_down(grid, ro, co);
    }
}

vector<string> simulate(vector<string> grid) {
    const int W = sz(grid[0]);
    for (int co = 0; co < W; ++co) simulate_column(grid, co);
    return grid;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t;
    cin >> t;
    while (t--) {
        int H, W;
        cin >> H >> W;

        vector<string> grid(H);
        for (auto &row : grid) {
            cin >> row;
            assert(sz(row) == W);
        }

        for (const auto &row : simulate(grid)) {
            cout << row << '\n';
        }
    }

    return 0;
}
