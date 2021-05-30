#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace std;
using namespace __gnu_pbds;
template <typename T>
using ordered_set =
    tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

using vi = vector<int>;
using vvi = vector<vi>;
using pii = pair<int, int>;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

static constexpr int INF = 1e9 + 7;

int mhash(const int ro, const int co) {
    return inof(31 * hash<int>{}(ro) + hash<int>{}(co));
}

template <typename T> constexpr T div_ceil(const T x, const T y) {
    return x ? (1 + (x - 1) / y) : 0;
}

int stride_down(const int k, const vvi &grid, const int co,
                ordered_set<pii> window) {
    const int n = sz(grid);
    const int m = div_ceil(k * k, 2) - 1;
    int ans = window.find_by_order(m)->first;
    int ro = 0;

    while (ro + 1 + k <= n) {
        for (int j = co; j < co + k; ++j) {
            window.erase(pii{grid[ro][j], mhash(ro, j)});
            window.insert(pii{grid[ro + k][j], mhash(ro + k, j)});
        }

        ans = min(ans, window.find_by_order(m)->first);
        ++ro;
    }

    return ans;
}

int lowest_median(const int k, const vvi &grid) {
    const int n = sz(grid);
    ordered_set<pii> window;

    for (int ro = 0; ro < k; ++ro) {
        for (int co = 0; co < k; ++co) {
            window.insert({grid[ro][co], mhash(ro, co)});
        }
    }

    int ans = INF;
    ans = min(ans, stride_down(k, grid, 0, window));

    int co = 0;
    while (co + 1 + k <= n) {
        for (int i = 0; i < k; ++i) {
            window.erase(pii{grid[i][co], mhash(i, co)});
            window.insert(pii{grid[i][co + k], mhash(i, co + k)});
        }

        ans = min(ans, stride_down(k, grid, co, window));
        ++co;
    }

    return ans;
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
