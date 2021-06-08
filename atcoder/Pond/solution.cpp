#include <bits/stdc++.h>
using namespace std;

using vi = vector<int>;
using vvi = vector<vi>;
using pii = pair<int, int>;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

vvi lte_indicators(const vvi &grid, const int level) {
    const int n = sz(grid);
    vvi ans(n, vi(n));

    for (int ro = 0; ro < n; ++ro) {
        for (int co = 0; co < n; ++co) {
            ans[ro][co] = grid[ro][co] <= level ? 1 : 0;
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

template <typename T> constexpr T div_ceil(const T x, const T y) {
    return x ? (1 + (x - 1) / y) : 0;
}

bool is_median_up_to_level_possible(const vvi &grid, const int k,
                                    const int level) {
    const int n = sz(grid);
    const auto ps = prefix_sums(lte_indicators(grid, level));

    const auto kxk_sum_from = [&](const int ro, const int co) -> int {
        auto ans = ps[ro + k - 1][co + k - 1];
        if (ro > 0) ans -= ps[ro - 1][co + k - 1];
        if (co > 0) ans -= ps[ro + k - 1][co - 1];
        if (ro > 0 && co > 0) ans += ps[ro - 1][co - 1];
        return ans;
    };

    const int edge = div_ceil(k * k, 2);

    for (int ro = 0; ro + k <= n; ++ro) {
        for (int co = 0; co + k <= n; ++co) {
            if (kxk_sum_from(ro, co) >= edge) return true;
        }
    }

    return false;
}

static constexpr int INF = 1e9 + 111;

pii minmax_2d(const vvi &xss) {
    vector<pii> byrow(sz(xss));
    transform(cbegin(xss), cend(xss), begin(byrow), [](const vi &row) {
        const auto [lo, hi] = minmax_element(cbegin(row), cend(row));
        return pii{*lo, *hi};
    });

    return accumulate(
        cbegin(byrow), cend(byrow), pii{INF, -INF},
        [](const pii agg, const pii xy) {
            return pii{min(agg.first, xy.first), max(agg.second, xy.second)};
        });
}

int lowest_median(const vvi &grid, const int k) {
    auto [lo, hi] = minmax_2d(grid);
    --lo;

    while (hi - lo > 1) {
        const int mid = lo + (hi - lo) / 2;
        if (is_median_up_to_level_possible(grid, k, mid)) {
            hi = mid;
        } else {
            lo = mid;
        }
    }

    return hi;
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

    cout << lowest_median(grid, k) << '\n';
    return 0;
}
