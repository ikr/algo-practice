#include <bits/stdc++.h>
using namespace std;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

using pii = pair<int, int>;

int min_ops(const vector<string> &grid) {
    const auto n = sz(grid);
    int result{};

    vector<vector<bool>> done(n, vector(n, false));

    for (int ro = 0; ro < n; ++ro) {
        for (int co = 0; co < n; ++co) {
            if (done[ro][co]) continue;

            int zeros{};
            int ones{};
            zeros += grid[ro][co] == '0';
            ones += grid[ro][co] == '1';

            const auto ro1 = co;
            const auto co1 = n - 1 - ro;
            zeros += grid[ro1][co1] == '0';
            ones += grid[ro1][co1] == '1';
            done[ro1][co1] = true;

            const auto ro2 = co1;
            const auto co2 = n - 1 - ro1;
            zeros += grid[ro2][co2] == '0';
            ones += grid[ro2][co2] == '1';
            done[ro2][co2] = true;

            const auto ro3 = co2;
            const auto co3 = n - 1 - ro2;
            zeros += grid[ro3][co3] == '0';
            ones += grid[ro3][co3] == '1';
            done[ro3][co3] = true;

            result += min(zeros, ones);
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

        vector<string> grid(n);
        for (auto &row : grid) {
            cin >> row;
            assert(sz(row) == n);
        }

        cout << min_ops(grid) << '\n';
    }

    return 0;
}
