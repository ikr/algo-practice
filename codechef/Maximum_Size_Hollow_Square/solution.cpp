#include <bits/stdc++.h>
using namespace std;
using Coord = pair<int, int>;

vector<vector<int>> gather_prefix_sums(const vector<string> &rows) {
    const int h = rows.size();
    const int w = rows[0].size();

    vector<vector<int>> ans(h, vector<int>(w, 0));
    for (int ro = 0; ro < h; ++ro) {
        for (int co = 0; co < w; ++co) {
            if (ro > 0) ans[ro][co] += ans[ro - 1][co];
            if (co > 0) ans[ro][co] += ans[ro][co - 1];
            if (ro > 0 && co > 0) ans[ro][co] -= ans[ro - 1][co - 1];
            ans[ro][co] += rows[ro][co] - '0';
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

bool is_possible(const int k, const vector<vector<int>> &ss,
                 const Coord right_bottom, const int side) {
    const int h = ss.size();
    const int w = ss[0].size();

    const int s_inside = sum_inside_square(ss, right_bottom, side);
    const int s_outside = ss.back().back() - s_inside;
    const int z_outside = h * w - side * side - s_outside;

    return z_outside >= s_inside && s_inside <= k;
}

int max_hollow_square_side_at(const int k, const vector<vector<int>> &ss,
                              const Coord right_bottom) {
    if (!is_possible(k, ss, right_bottom, 1)) return 0;
    int hi = max_square_side(right_bottom);
    if (is_possible(k, ss, right_bottom, hi)) return hi;

    int lo = 1;
    int ans = lo;

    while (lo <= hi) {
        const int mid = lo + (hi - lo) / 2;
        if (is_possible(k, ss, right_bottom, mid)) {
            ans = mid;
            lo = mid + 1;
        } else {
            hi = mid - 1;
        }
    }

    return ans;
}

int max_hollow_square_side(const vector<string> &rows, const int k) {
    const auto ss = gather_prefix_sums(rows);
    const int h = rows.size();
    const int w = rows[0].size();

    int ans = 0;
    for (int ro = 0; ro < h; ++ro) {
        for (int co = 0; co < w; ++co) {
            ans = max(ans, max_hollow_square_side_at(k, ss, {ro, co}));
        }
    }

    return ans;
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
