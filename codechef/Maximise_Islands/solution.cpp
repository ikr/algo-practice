#include <bits/stdc++.h>
using namespace std;
using CB = pair<vector<string>, int>;

pair<CB, CB> chess_boards(const int h, const int w) {
    vector<string> rows_a(h, string(w, '.'));
    int land_a = 0;

    vector<string> rows_b(h, string(w, '.'));
    int land_b = 0;

    for (int ro = 0; ro < h; ++ro) {
        for (int co = 0; co < w; ++co) {
            if ((ro + co) % 2) {
                rows_a[ro][co] = '*';
                ++land_a;
            } else {
                rows_b[ro][co] = '*';
                ++land_b;
            }
        }
    }

    return {{rows_a, land_a}, {rows_b, land_b}};
}

int count_diffs(const vector<string> &rows_a, const vector<string> &rows_b) {
    const int h = rows_a.size();
    const int w = rows_a[0].size();
    int ans = 0;

    for (int ro = 0; ro < h; ++ro) {
        for (int co = 0; co < w; ++co) {
            if (rows_a[ro][co] != rows_b[ro][co]) ++ans;
        }
    }

    return ans;
}

int min_ops(const vector<string> &rows) {
    const int h = rows.size();
    const int w = rows[0].size();

    const auto [cb_a, cb_b] = chess_boards(h, w);

    if (cb_a.second == cb_b.second) {
        return min(count_diffs(rows, cb_a.first),
                   count_diffs(rows, cb_b.first));
    }

    const auto &cb = cb_a.second > cb_b.second ? cb_a.first : cb_b.first;
    return count_diffs(rows, cb);
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int t;
    cin >> t;
    while (t--) {
        int h, w;
        cin >> h >> w;

        vector<string> rows(h, string(w, ' '));
        for (auto &r : rows) cin >> r;
        cout << min_ops(rows) << '\n';
    }

    return 0;
}
