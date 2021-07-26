#include <bits/stdc++.h>
using namespace std;

int solve(const vector<int> &xs) {
    const int n = xs.size();
    set<int> ds;

    for (int i = 0; i < n - 1; ++i) {
        for (int j = i + 1; j < n; ++j) {
            ds.insert(xs[j] - xs[i]);
        }
    }

    return ds.size();
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;

        vector<int> xs(n, 0);
        for (auto &x : xs) cin >> x;

        cout << solve(xs) << '\n';
    }

    return 0;
}
