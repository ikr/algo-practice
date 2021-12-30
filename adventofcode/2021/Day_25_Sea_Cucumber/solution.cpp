#include <bits/stdc++.h>
using namespace std;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

vector<string> evolve(vector<string> grid) {
    const int H = sz(grid);
    const int W = sz(grid[0]);

    for (int ro = 0; ro < H; ++ro) {
        const auto org_l = grid[ro][0];
        const auto org_r = grid[ro].back();

        for (int co = W - 2; co >= 0; --co) {
            if (grid[ro][co] == '>' && grid[ro][co + 1] == '.') {
                grid[ro][co] = '.';
                grid[ro][co + 1] = '>';
            }
        }

        if (org_r == '>' && org_l == '.') {
            grid[ro].back() = '.';
            grid[ro][0] = '>';
        }
    }

    for (int co = 0; co < H; ++co) {
        const auto org_t = grid[0][co];
        const auto org_b = grid[H - 1][co];

        for (int ro = H - 2; ro >= 0; --ro) {
            if (grid[ro][co] == 'v' && grid[ro + 1][co] == '.') {
                grid[ro][co] = '.';
                grid[ro + 1][co] = 'v';
            }
        }

        if (org_b == 'v' && org_t == '.') {
            grid[H - 1][co] = '.';
            grid[0][co] = 'v';
        }
    }

    return grid;
}

void dump_grid(const vector<string> &grid) {
    for (const auto &row : grid) {
        cerr << row << endl;
    }
    cerr << endl;
}

int main() {
    vector<string> grid;
    for (string line; getline(cin, line);) {
        grid.push_back(line);
    }

    for (int i = 1; i <= 4; ++i) {
        grid = evolve(grid);
        dump_grid(grid);
    }
    return 0;
}
