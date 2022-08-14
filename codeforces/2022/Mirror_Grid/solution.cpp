#include <bits/stdc++.h>
using namespace std;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

using Grid = vector<string>;

Grid rotate_right(const Grid &grid) {
    const auto n = sz(grid);
    Grid result(n, string(n, ' '));

    for (int ro = 0; ro < n; ++ro) {
        for (int co = 0; co < n; ++co) {
            result[co][n - 1 - ro] = grid[ro][co];
        }
    }

    return result;
}

array<Grid, 4> all_rotrations(const Grid &grid) {
    array<Grid, 4> result;
    result[0] = grid;

    for (int i = 1; i < sz(result); ++i) {
        result[i] = rotate_right(result[i - 1]);
    }

    return result;
}

int min_ops(const Grid &grid) {
    const auto n = sz(grid);
    auto rs = all_rotrations(grid);
    int result{};

    for (int ro = 0; ro < n; ++ro) {
        for (int co = 0; co < n; ++co) {
            int zeros{};
            int ones{};

            for (int i = 0; i < sz(rs); ++i) {
                zeros += rs[i][ro][co] == '0';
                ones += rs[i][ro][co] == '1';
            }

            if (min(zeros, ones) == 0) continue;

            result += min(zeros, ones);
            const auto val = zeros < ones ? '1' : '0';

            const auto ro1 = co;
            const auto co1 = n - 1 - ro;
            rs[1][ro1][co1] = val;

            const auto ro2 = co1;
            const auto co2 = n - 1 - ro1;
            rs[2][ro2][co2] = val;

            const auto ro3 = co2;
            const auto co3 = n - 1 - ro2;
            rs[3][ro3][co3] = val;
        }
    }

    return result;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;

        Grid grid(n);
        for (auto &row : grid) {
            cin >> row;
            assert(sz(row) == n);
        }

        cout << min_ops(grid) << '\n';
    }

    return 0;
}
