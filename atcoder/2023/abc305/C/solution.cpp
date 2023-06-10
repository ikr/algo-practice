#include <bits/stdc++.h>
using namespace std;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

pair<int, int> find_eaten(const vector<string> &grid) {
    const auto H = sz(grid);
    const auto W = sz(grid[0]);

    int ro_lo = INT_MAX;
    int co_lo = INT_MAX;
    int ro_hi = INT_MIN;
    int co_hi = INT_MIN;

    for (int ro = 0; ro < H; ++ro) {
        for (int co = 0; co < W; ++co) {
            if (grid[ro][co] == '.') continue;

            ro_lo = min(ro_lo, ro);
            co_lo = min(co_lo, co);

            ro_hi = max(ro_hi, ro);
            co_hi = max(co_hi, co);
        }
    }

    for (int ro = ro_lo; ro <= ro_hi; ++ro) {
        for (int co = co_lo; co <= co_hi; ++co) {
            if (grid[ro][co] == '.') return {ro, co};
        }
    }

    assert(false);
    return {-1, -1};
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int H, W;
    cin >> H >> W;

    vector<string> grid(H);
    for (auto &row : grid) cin >> row;

    const auto [ro, co] = find_eaten(grid);
    cout << (ro + 1) << ' ' << (co + 1) << '\n';
    return 0;
}
