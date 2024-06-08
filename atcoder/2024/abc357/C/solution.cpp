#include <bits/stdc++.h>
using namespace std;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

int power_of_3(const int x) { return x ? 3 * power_of_3(x - 1) : 1; }

void cut_holes(vector<string> &grid, const int left, const int top,
               const int n) {
    if (n == 1) return;
    assert(n % 3 == 0);
    const auto m = n / 3;
    for (int r = top + m; r < top + 2 * m; ++r) {
        for (int c = left + m; c < left + 2 * m; ++c) {
            grid[r][c] = '.';
        }
    }

    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (i == 1 && j == 1) continue;
            cut_holes(grid, left + i * m, top + j * m, m);
        }
    }
}

vector<string> new_carpet(const int k) {
    const auto n = power_of_3(k);
    vector<string> grid(n, string(n, '#'));
    cut_holes(grid, 0, 0, n);
    return grid;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int k;
    cin >> k;

    for (const auto &row : new_carpet(k)) {
        cout << row << '\n';
    }
    return 0;
}
