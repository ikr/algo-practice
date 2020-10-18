#include <bits/stdc++.h>
using namespace std;
using ll = long long;

ll solve(const vector<vector<int>> &rows) {
    const int n = rows.size();
    ll ans = 0;

    for (int i = 0; i < n; ++i) {
        int r = 0;
        int c = i;

        ll candidate = 0;
        while (r < n && c < n) {
            candidate += rows[r][c];
            ++r;
            ++c;
        }

        ans = max(ans, candidate);
    }

    for (int i = 1; i < n; ++i) {
        int r = i;
        int c = 0;

        ll candidate = 0;
        while (r < n && c < n) {
            candidate += rows[r][c];
            ++r;
            ++c;
        }

        ans = max(ans, candidate);
    }

    return ans;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int t;
    cin >> t;
    for (int i = 1; i <= t; ++i) {
        int n;
        cin >> n;
        vector<vector<int>> rows(n, vector<int>(n, 0));
        for (auto &row : rows) {
            for (auto &x : row) cin >> x;
        }

        cout << "Case #" << i << ": " << solve(rows) << '\n';
    }

    return 0;
}
