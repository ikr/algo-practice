#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

using ll = long long;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

ll backslash_sum(const vector<vector<int>> &grid, const int ro0,
                 const int co0) {
    ll result = grid[ro0][co0];
    {
        int ro = ro0;
        int co = co0;

        while (ro - 1 >= 0 && co - 1 >= 0) {
            --ro;
            --co;
            result += grid[ro][co];
        }
    }

    {
        int ro = ro0;
        int co = co0;

        while (ro + 1 < sz(grid) && co + 1 < sz(grid[0])) {
            ++ro;
            ++co;
            result += grid[ro][co];
        }
    }

    return result;
}

ll slash_sum(const vector<vector<int>> &grid, const int ro0, const int co0) {
    ll result = grid[ro0][co0];
    {
        int ro = ro0;
        int co = co0;

        while (ro + 1 < sz(grid) && co - 1 >= 0) {
            ++ro;
            --co;
            result += grid[ro][co];
        }
    }

    {
        int ro = ro0;
        int co = co0;

        while (ro - 1 >= 0 && co + 1 < sz(grid[0])) {
            --ro;
            ++co;
            result += grid[ro][co];
        }
    }

    return result;
}

ll max_sum(const vector<vector<int>> &grid) {
    const auto H = sz(grid);
    const auto W = sz(grid[0]);

    ll result{};

    for (int ro = 0; ro < H; ++ro) {
        for (int co = 0; co < W; ++co) {
            result =
                max(result, slash_sum(grid, ro, co) +
                                backslash_sum(grid, ro, co) - grid[ro][co]);
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
        int H, W;
        cin >> H >> W;

        vector<vector<int>> grid(H, vector<int>(W));
        for (auto &row : grid) {
            for (auto &x : row) cin >> x;
        }

        cout << max_sum(grid) << '\n';
    }

    return 0;
}
