#include <bits/stdc++.h>
using namespace std;

vector<string> chess_board(const int h, const int w) {
    vector<string> rows_a(h, string(w, '.'));
    int land_a = 0;
    for (int ro = 0; ro < h; ++ro) {
        for (int co = 0; co < w; ++co) {
            if ((ro + co) % 2 == 0) {
                rows_a[ro][co] = '*';
                ++land_a;
            }
        }
    }

    vector<string> rows_b(h, string(w, '.'));
    int land_b = 0;
    for (int ro = 0; ro < h; ++ro) {
        for (int co = 0; co < w; ++co) {
            if ((ro + co) % 2) {
                rows_b[ro][co] = '*';
                ++land_b;
            }
        }
    }

    return land_a > land_b ? rows_a : rows_b;
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

    return count_diffs(rows, chess_board(h, w));
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
