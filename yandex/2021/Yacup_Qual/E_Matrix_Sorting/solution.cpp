#include <algorithm>
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

    // D[i][j][k] — when there are i ones total already placed, counted up to
    // the row j, when in that row is exactly k ones.
    vector<vvi> D(M + 1, vvi(H, vi(W + 1, INF)));

    for (int m = 0; m <= min(M, W); ++m) {
        D[m][0][m] = num_moves(0, m);
    }

    for (int ro = 1; ro < H; ++ro) {
        for (int n = 0; n <= min(M, W); ++n) { // # of 1-s placed in this row
            const int m_lo = min((ro + 1) * n, M);
            const int m_hi = min(n + ro * W, M);

            int opt = INF;
            for (int m = m_lo; m <= m_hi; ++m) {
                for (int k = n; k <= min(W, m - n); ++k) {
                    opt = min(opt, D[m - n][ro - 1][k]);
                }

                D[m][ro][n] = opt + num_moves(ro, n);
            }
        }
    }

    const auto &edge = D[M][H - 1];
    return *min_element(cbegin(edge), cend(edge));
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
