#include <bits/stdc++.h>
using namespace std;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

void place_into_row(string &row) {
    for (string::size_type i = 0;;) {
        const auto j = row.find("TT", i);
        if (j == row.npos) break;

        row[j] = 'P';
        row[j + 1] = 'C';
        i = j + 2;
        if (i == row.size()) break;
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int H, W;
    cin >> H >> W;

    vector<string> grid(H);
    for (auto &row : grid) {
        cin >> row;
        assert(sz(row) == W);

        place_into_row(row);
        cout << row << '\n';
    }

    return 0;
}
