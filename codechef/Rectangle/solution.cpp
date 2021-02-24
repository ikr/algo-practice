#include <bits/stdc++.h>
using namespace std;
using pi = pair<int, int>;

vector<pi> gather_sorted_coords_of_ones(const vector<string> &rows) {
    const int h = rows.size();
    const int w = rows[0].size();

    vector<pi> ans;

    for (int ro = 0; ro < h; ++ro) {
        for (int co = 0; co < w; ++co) {
            if (rows[ro][co] == '1') ans.emplace_back(ro, co);
        }
    }

    sort(begin(ans), end(ans));
    return ans;
}

bool is_rect_of_ones(const vector<string> &rows) {
    const auto cs = gather_sorted_coords_of_ones(rows);
    const auto lt = cs[0];
    const auto rb = cs.back();

    const int h = rb.first - lt.first + 1;
    const int w = rb.second - lt.second + 1;
    const int k = cs.size();

    if (k != h * w) return false;

    for (int i = 1; i < k - 1; ++i) {
        const bool ok = lt.first <= cs[i].first && lt.second <= cs[i].second &&
                        cs[i].first <= rb.first && cs[i].second <= rb.second;
        if (!ok) return false;
    }

    return true;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int t;
    cin >> t;
    while (t--) {
        int n, m;
        cin >> n >> m;

        vector<string> rows(n, string(m, ' '));
        for (auto &row : rows) cin >> row;

        cout << (is_rect_of_ones(rows) ? "YES\n" : "NO\n");
    }

    return 0;
}
