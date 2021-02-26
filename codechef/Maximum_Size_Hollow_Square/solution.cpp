#include <bits/stdc++.h>
using namespace std;
using Coord = pair<int, int>;

vector<vector<int>> gather_prefix_sums(const vector<string> &rows) {
    const int h = rows.size();
    const int w = rows[0].size();

    vector<vector<int>> ans(h, vector<int>(w, 0));
    for (int ro = 0; ro < h; ++ro) {
        for (int co = 0; co < w; ++co) {
            if (ro > 0) ans[ro][co] += rows[ro - 1][co] - '0';
            if (co > 0) ans[ro][co] += rows[ro][co - 1] - '0';
            ans[ro][co] += rows[ro][co];
        }
    }
    return ans;
}

int max_square_side(const Coord right_bottom) {
    const auto [ro, co] = right_bottom;
    return min(ro + 1, co + 1);
}

int sum_inside_square(const vector<vector<int>> &ss, const Coord right_bottom,
                      const int side) {
    const auto [ro, co] = right_bottom;
    const Coord left_top{ro - side + 1, co - side + 1};
    assert(left_top.first >= 0 && left_top.second >= 0);

    const int north_area =
        left_top.first > 0 ? ss[left_top.first - 1][right_bottom.second] : 0;
    const int west_area =
        left_top.second > 0 ? ss[right_bottom.first][left_top.second - 1] : 0;
    const int north_west_area =
        left_top.first > 0 && left_top.second > 0
            ? ss[left_top.first - 1][left_top.second - 1]
            : 0;

    return ss[ro][co] - north_area - west_area + north_west_area;
}

int max_hollow_square_side(const vector<string> &rows, const int k) {
    const auto ss = gather_prefix_sums(rows);
    const int h = rows.size();
    const int w = rows[0].size();

    for (int ro = 0; ro < h; ++ro) {
        for (int co = 0; co < w; ++co) {
        }
    }

    return -1;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int t;
    cin >> t;
    while (t--) {
        int h, w, k;
        cin >> h >> w >> k;

        vector<string> rows(h, string(w, ' '));
        for (auto &row : rows) cin >> row;

        cout << max_hollow_square_side(rows, k) << '\n';
    }

    return 0;
}
