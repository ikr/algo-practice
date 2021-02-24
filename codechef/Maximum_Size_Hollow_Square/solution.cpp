#include <bits/stdc++.h>
using namespace std;

vector<vector<int>> gather_prefix_sums(const vector<string> &rows) {
    const int h = rows.size();
    const int w = rows[0].size();

    vector<vector<int>> ans(h, vector<int>(w, 0));
    for (int ro = 0; ro < h; ++ro) {
        for (int co = 0; co < w; ++co) {
            if (ro > 0) ans[ro][co] += rows[ro - 1][co] - '0';
            if (co > 0) ans[ro][co] += rows[ro][co - 1] - '0';
        }
    }
    return ans;
}

int max_hollow_square_side(const vector<string> &rows, const int k) {
    const auto ss = gather_prefix_sums(rows);
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
