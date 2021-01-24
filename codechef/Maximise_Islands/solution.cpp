#include <bits/stdc++.h>
using namespace std;

template <typename T> ostream &operator<<(ostream &os, const vector<T> &xs) {
    os << '[';
    for (auto i = xs.cbegin(); i != xs.cend(); ++i) {
        if (i != xs.cbegin()) os << ' ';
        os << *i;
    }
    os << ']';
    return os;
}

vector<string> chess_board(const int h, const int w) {
    vector<string> rows(h, string(w, '.'));
    for (int ro = 0; ro < h; ++ro) {
        for (int co = 0; co < w; ++co) {
            if ((ro + co) % 2) rows[ro][co] = '*';
        }
    }
    return rows;
}

vector<string> flip_chess_board(const vector<string> &rows) {
    const int h = rows.size();
    const int w = rows[0].size();
    vector<string> ans(h, string(w, ' '));

    for (int ro = 0; ro < h; ++ro) {
        for (int co = 0; co < w; ++co) {
            ans[ro][co] = rows[ro][co] == '*' ? '.' : '*';
        }
    }
    return ans;
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

    const auto cb_a = chess_board(h, w);
    const auto cb_b = flip_chess_board(cb_a);

    return min(count_diffs(rows, cb_a), count_diffs(rows, cb_b));
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
