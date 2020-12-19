#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int h, w;
    cin >> h >> w;

    vector<vector<int>> rows(h, vector<int>(w, 0));

    int lo = 1e9;
    for (int ro = 0; ro < h; ++ro) {
        for (int co = 0; co < w; ++co) {
            cin >> rows[ro][co];
            lo = min(lo, rows[ro][co]);
        }
    }

    int ans = 0;

    for (const auto &row : rows) {
        for (const int x : row) {
            ans += x - lo;
        }
    }

    cout << ans << '\n';
    return 0;
}
