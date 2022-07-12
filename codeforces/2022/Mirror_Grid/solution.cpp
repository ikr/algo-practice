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

int min_ops_in_a_circle(const string &xs) {
    const auto ones = count(cbegin(xs), cend(xs), '1');
    const auto zeros = count(cbegin(xs), cend(xs), '0');
    if (!ones || !zeros) return 0;
    return inof(min(ones, zeros));
}

int min_ops(const vector<string> &grid) {
    const auto n = sz(grid);
    int result{};

    for (int i = 0; i < div_ceil(n, 2); ++i) {
        const auto d = n - 2 * i;
        cerr << "i:" << i << " d:" << d << endl;
        if (d == 1) continue;

        const string rect{grid[i][i], grid[i][i + d - 1],
                          grid[i + d - 1][i + d - 1], grid[i + d - 1][i]};
        result += min_ops_in_a_circle(rect);
        cerr << "rect:" << rect << endl;

        if (d % 2) {
            const string cross{grid[i][i + d / 2], grid[i + d / 2][i + d - 1],
                               grid[i + d - 1][i + d / 2], grid[i + d / 2][i]};
            result += min_ops_in_a_circle(cross);
            cerr << "cross:" << cross << endl;
        }

        for (int j = 1; j < d / 2; ++j) {
            string xs;

            xs += grid[i][i + j];
            xs += grid[i][i + d - 1 - j];

            xs += grid[i + j][i + d - 1];
            xs += grid[i + d - 1 - j][i + d - 1];

            xs += grid[i + d - 1][i + j];
            xs += grid[i + d - 1][i + d - 1 - j];

            xs += grid[i + j][i];
            xs += grid[i + d - 1 - j][i];

            result += min_ops_in_a_circle(xs);
            cerr << "j:" << j << " xs:" << xs << endl;
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
