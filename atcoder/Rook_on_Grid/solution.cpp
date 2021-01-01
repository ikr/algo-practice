#include <bits/stdc++.h>
using namespace std;
using ll = long long;

ll reachable_squares_count(const int h, const int w,
                           vector<pair<int, int>> obstacles) {
    sort(begin(obstacles), end(obstacles));

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

    return ans;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int h, w, m;
    cin >> h >> w >> m;

    vector<pair<int, int>> obstacles(m);
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
