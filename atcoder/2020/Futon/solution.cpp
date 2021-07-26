#include <bits/stdc++.h>
using namespace std;

int count_ways(const vector<string> &rows) {
    const int H = rows.size();
    const int W = rows[0].size();

    int ans = 0;

    for (int i = 0; i < H; ++i) {
        for (int j = 0; j < W; ++j) {
            if (i != H - 1 && rows[i][j] == '.' && rows[i + 1][j] == '.') ++ans;
            if (j != W - 1 && rows[i][j] == '.' && rows[i][j + 1] == '.') ++ans;
        }
    }

    return ans;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int H, W;
    cin >> H >> W;
    vector<string> rows(H, string(W, ' '));

    for (auto &row : rows) cin >> row;
    cout << count_ways(rows) << '\n';

    return 0;
}
