#include <atcoder/fenwicktree>
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

ll reachable_squares_count(const int h, const int w,
                           vector<pair<int, int>> obstacles) {
    vector<int> obstacle_row_by_col(w, h);
    vector<int> obstacle_col_by_row(h, w);
    vector<vector<int>> obstacle_cols_by_row(h);

    for (const auto &[ro, co] : obstacles) {
        obstacle_row_by_col[co] = min(obstacle_row_by_col[co], ro);
        obstacle_col_by_row[ro] = min(obstacle_col_by_row[ro], co);
        obstacle_cols_by_row[ro].push_back(co);
    }

    ll ans = 0;
    for (int co = 0; co < obstacle_col_by_row[0]; ++co) {
        ans += obstacle_row_by_col[co];
    }

    atcoder::fenwick_tree<int> tops(w);
    for (int ro = 0; ro < obstacle_row_by_col[0]; ++ro) {
        if (obstacle_col_by_row[ro] > obstacle_col_by_row[0]) {
            ans += obstacle_col_by_row[ro] - obstacle_col_by_row[0];
        }

        ans +=
            tops.sum(0, min(obstacle_col_by_row[ro], obstacle_col_by_row[0]));

        for (const int co : obstacle_cols_by_row[ro]) {
            if (tops.sum(co, co + 1)) continue;
            tops.add(co, 1);
        }
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
