#include <bits/stdc++.h>
using namespace std;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

template <typename T> constexpr T div_ceil(const T x, const T y) {
    return x ? (1 + (x - 1) / y) : 0;
}

vector<string> transpose(const vector<string> &grid) {
    vector<string> result = grid;

    for (int ro = 0; ro < sz(grid); ++ro) {
        assert(sz(result) == sz(result[ro]));

        for (int co = 0; co < sz(grid); ++co) {
            result[ro][co] = grid[co][ro];
        }
    }

    return result;
}

vector<string> flip_rows(vector<string> grid) {
    const auto n = sz(grid);

    for (int i = 0; i < n / 2; ++i) {
        swap(grid[i], grid[n - 1 - i]);
    }

    return grid;
}

pair<vector<string>, int> top_down_overwrite_ops(vector<string> grid) {
    const auto n = sz(grid);

    int ops{};

    for (int i = 0; i < n / 2; ++i) {
        const bitset<100> hi(grid[i]);
        const bitset<100> lo(grid[n - 1 - i]);
        ops += inof((hi ^ lo).count());

        grid[n - 1 - i] = grid[i];
    }

    return {grid, ops};
}

int min_ops(const vector<string> &grid) {
    if (sz(grid) == 1) return 0;
    set<int> opt;

    {
        auto [g, a] = top_down_overwrite_ops(grid);
        auto [_, b] = top_down_overwrite_ops(transpose(g));
        opt.insert(a + b);
    }

    return *cbegin(opt);
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;

        vector<string> grid(n);
        for (auto &row : grid) {
            cin >> row;
            assert(sz(row) == n);
        }

        cout << min_ops(grid) << '\n';
    }

    return 0;
}
