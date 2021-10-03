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

vvi grid_prefix_sums(const vector<string> &grid) {
    const int H = sz(grid);
    const int W = sz(grid[0]);
    vvi pss(H, vi(W, 0));

    for (int ro = 0; ro < H; ++ro) {
        int curr = 0;

        for (int co = 0; co < W; ++co) {
            if (grid[ro][co] == '1') ++curr;
            pss[ro][co] = curr;
        }
    }

    return pss;
}

int total_onses(const vector<string> &grid) {
    int ans = 0;

    for (const auto &row : grid) {
        ans += inof(count(cbegin(row), cend(row), '1'));
    }

    return ans;
}

static constexpr int INF = 1e9;

int min_swaps(const vector<string> &grid) {
    const int H = sz(grid);
    const int W = sz(grid[0]);
    const int M = total_onses(grid);
    const auto pss = grid_prefix_sums(grid);

    const auto num_moves = [&](const int ro, const int target_ones) {
        assert(target_ones <= W);
        const auto initial_ones = target_ones ? pss[ro][target_ones - 1] : 0;
        const auto extra_ones = pss[ro].back() - initial_ones;

        if (initial_ones == target_ones) {
            return extra_ones;
        }

        assert(initial_ones < target_ones);
        const int d = target_ones - initial_ones;
        return d + max(0, extra_ones - d);
    };

    function<int(int, int, int)> recur;
    recur = [&](const int m, const int ro, const int hi) -> int {
        if (m <= 0 || ro >= H) return 0;

        int ans = INF;
        for (int n = 0; n <= hi; ++n) { // # of 1s placed in the row
            if (m - n <= 0) break;
            ans = min(ans, recur(m - n, ro + 1, n) + num_moves(ro, n));
        }

        return ans;
    };

    return recur(M, 0, min(M, W));
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int H, W;
    cin >> H >> W;

    vector<string> grid(H, string(W, ' '));
    for (auto &row : grid) {
        cin >> row;
        reverse(begin(row), end(row));
    }
    reverse(begin(grid), end(grid));

    cout << min_swaps(grid) << '\n';
    return 0;
}
