#include <bits/stdc++.h>
using namespace std;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

int min_ops(const vector<vector<bool>> &grid) {
    const auto n = sz(grid);
    vector<bool> flipped(n, false);

    const auto dyn_get = [&](const int ro, const int co) -> bool {
        return flipped[ro] ? !grid[ro][co] : grid[ro][co];
    };

    const auto to_keep = [&](const int co) -> bool {
        int zs{};
        int os{};
        for (int ro = 0; ro < n; ++ro) {
            if (dyn_get(ro, co)) {
                ++os;
            } else {
                ++zs;
            }
        }

        return zs >= os ? false : true;
    };

    int result{};
    const auto m = sz(grid[0]);

    for (int co = 0; co < m; ++co) {
        const auto tk = to_keep(co);

        for (int ro = 0; ro < n; ++ro) {
            if (dyn_get(ro, co) != tk) {
                ++result;
                flipped[ro] = !flipped[ro];
            }
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
        int n, m;
        cin >> n >> m;

        vector<vector<bool>> grid(n, vector(m, false));
        for (auto &row : grid) {
            string src;
            cin >> src;

            transform(cbegin(src), cend(src), begin(row),
                      [](const char d) { return d == '1'; });
            reverse(begin(row), end(row));
        }

        cout << min_ops(grid) << '\n';
    }

    return 0;
}
