#include <bits/stdc++.h>
using namespace std;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

vector<string> transpose(const vector<string> &m) {
    const auto H = sz(m[0]);
    const auto W = sz(m);

    vector<string> ans(H, string(W, ' '));
    for (int ro = 0; ro < H; ++ro) {
        for (int co = 0; co < W; ++co) {
            ans[ro][co] = m[co][ro];
        }
    }
    return ans;
}

int smudges_count(const string &xs) {
    int result{};
    for (int i = 0, j = sz(xs) - 1; i < j; ++i, --j) {
        result += xs[i] != xs[j];
    }
    return result;
}

bool are_columns_mirrored(const vector<string> &grid, const int c0,
                          const int d0) {
    const auto lc = c0 - d0 + 1;
    const auto rc = c0 + d0;
    if (lc < 0 || rc >= sz(grid[0])) return false;
    if (lc != 0 && rc != sz(grid[0]) - 1) return false;

    int ss{};
    for (const auto &row : grid) {
        ss += smudges_count(row.substr(lc, 2 * d0));
    }
    return ss == 1;
}

int reflection_col(const vector<string> &grid) {
    const auto W = sz(grid[0]);
    for (int d = W / 2 + 1; d >= 1; --d) {
        for (int c = 0; c < W; ++c) {
            if (are_columns_mirrored(grid, c, d)) return c;
        }
    }
    return -1;
}

int digest(const int rc, const int rr) {
    if (rc == -1 && rr == -1) return 0;
    if (rr == -1) return rc + 1;
    assert(rc == -1);
    return 100 * (rr + 1);
}

int main() {
    vector<vector<string>> grids(1);

    for (string line; getline(cin, line);) {
        if (empty(line)) {
            grids.emplace_back();
        } else {
            grids.back().push_back(line);
        }
    }

    int result{};

    for (const auto &grid : grids) {
        const auto rc = reflection_col(grid);
        const auto rr = reflection_col(transpose(grid));
        result += digest(rc, rr);
    }
    cout << result << '\n';
    return 0;
}
