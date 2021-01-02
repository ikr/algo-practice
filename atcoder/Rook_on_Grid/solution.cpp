#include <atcoder/lazysegtree>
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

constexpr int e() { return 0; }
constexpr bool id() { return false; }
constexpr int mplus(const int x, const int y) { return x + y; }
constexpr int mapping(const bool b, const int x) {
    return b ? (x > 0 ? 1 : 0) : 0;
}
constexpr bool composition(const bool a, const bool b) { return a || b; }

ll reachable_squares_count(const int h, const int w,
                           vector<pair<int, int>> obstacles) {
    vector<int> obstacle_row_by_col(w, h);
    vector<int> obstacle_col_by_row(h, w);

    for (const auto &[ro, co] : obstacles) {
        obstacle_row_by_col[co] = min(obstacle_row_by_col[co], ro);
        obstacle_col_by_row[ro] = min(obstacle_col_by_row[ro], co);
    }

    ll ans = 0;
    for (int co = 0; co < obstacle_col_by_row[0]; ++co) {
        ans += obstacle_row_by_col[co];
    }

    atcoder::lazy_segtree<int, mplus, e, bool, mapping, composition, id> tops(
        w);
    for (int ro = 0; ro < obstacle_row_by_col[0]; ++ro) {
        ans += tops.prod(0, obstacle_col_by_row[ro]);
        tops.apply(obstacle_col_by_row[ro], w, true);
    }

    return ans;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int h, w, m;
    cin >> h >> w >> m;

    vector<pair<int, int>> obstacles;
    while (m--) {
        int ro, co;
        cin >> ro >> co;
        --ro;
        --co;
        obstacles.emplace_back(ro, co);
    }

    cout << reachable_squares_count(h, w, move(obstacles)) << '\n';
    return 0;
}
