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
        vector<int> to_move;
        for (int co = 0; co < W; ++co) {
            if (grid[ro][co] == '>' && grid[ro][(co + 1) % W] == '.') {
                to_move.push_back(co);
            }
        }

        for (const auto co : to_move) {
            grid[ro][co] = '.';
            grid[ro][(co + 1) % W] = '>';
        }
    }

    for (int co = 0; co < W; ++co) {
        vector<int> to_move;
        for (int ro = 0; ro < H; ++ro) {
            if (grid[ro][co] == 'v' && grid[(ro + 1) % H][co] == '.') {
                to_move.push_back(ro);
            }
        }

        for (const auto ro : to_move) {
            grid[ro][co] = '.';
            grid[(ro + 1) % H][co] = 'v';
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

int first_step_without_movement(vector<string> grid) {
    for (int i = 1;; ++i) {
        auto grid_ = evolve(grid);
        if (grid_ == grid) return i;
        swap(grid, grid_);
    }
    return -1;
}

int main() {
    vector<string> grid;
    for (string line; getline(cin, line);) {
        grid.push_back(line);
    }

    cout << first_step_without_movement(move(grid)) << '\n';
    return 0;
}
