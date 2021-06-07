#include <bits/stdc++.h>
using namespace std;

template <typename T> ostream &operator<<(ostream &os, const vector<T> &xs) {
    os << '[';
    for (auto i = xs.cbegin(); i != xs.cend(); ++i) {
        if (i != xs.cbegin()) os << ' ';
        os << *i;
    }
    os << ']';
    return os;
}

template <typename T>
ostream &operator<<(ostream &os, const vector<vector<T>> &xss) {
    for (const auto xs : xss) os << xs << '\n';
    return os;
}

using vi = vector<int>;
using vvi = vector<vi>;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

static constexpr int INF = 1e9 + 7;

vvi gte_indicators(const vvi &grid, const int level) {
    const int n = sz(grid);
    vvi ans(n, vi(n));

    for (int ro = 0; ro < n; ++ro) {
        for (int co = 0; co < n; ++co) {
            ans[ro][co] = grid[ro][co] >= level ? 1 : 0;
        }
    }

    return ans;
}

vvi prefix_sums(vvi grid) {
    const int n = sz(grid);
    partial_sum(cbegin(grid[0]), cend(grid[0]), begin(grid[0]));
    for (int ro = 1; ro < n; ++ro) grid[ro][0] = grid[ro - 1][0] + grid[ro][0];

    for (int ro = 1; ro < n; ++ro) {
        for (int co = 1; co < n; ++co) {
            grid[ro][co] = grid[ro - 1][co] + grid[ro][co - 1] -
                           grid[ro - 1][co - 1] + grid[ro][co];
        }
    }

    return grid;
}

int lowest_median(const int k, const vvi &grid) {
    cerr << prefix_sums(grid) << endl;
    return -1;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int n, k;
    cin >> n >> k;

    vvi grid(n, vi(n, 0));
    for (auto &row : grid) {
        for (auto &x : row) cin >> x;
    }

    cout << lowest_median(k, grid) << '\n';
    return 0;
}
