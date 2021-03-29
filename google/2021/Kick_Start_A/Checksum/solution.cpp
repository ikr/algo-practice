#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vi = vector<int>;
using vvi = vector<vi>;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

pair<vi, vi> missing_count_by_row_by_col(const vvi &src) {
    vi by_row(sz(src), 0);
    vi by_col(sz(src), 0);

    for (int ro = 0; ro < sz(src); ++ro) {
        for (int co = 0; co < sz(src); ++co) {
            if (src[ro][co] == -1) {
                ++by_row[ro];
                ++by_col[co];
            }
        }
    }

    return {by_row, by_col};
}

ll solve(const vvi &src, const vvi &costs) { return -1; }

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    cout << setprecision(9) << fixed;

    int t;
    cin >> t;
    for (int i = 1; i <= t; ++i) {
        int n;
        cin >> n;

        vvi src(n, vi(n, 0));
        for (auto &line : src) {
            for (auto &cell : line) cin >> cell;
        }

        vvi costs(n, vi(n, 0));
        for (auto &line : costs) {
            for (auto &cell : line) cin >> cell;
        }

        vi rs(n, 0);
        for (auto &c : rs) cin >> c;

        vi cs(n, 0);
        for (auto &c : cs) cin >> c;

        cout << "Case #" << i << ": " << solve(src, costs) << '\n';
    }

    return 0;
}
