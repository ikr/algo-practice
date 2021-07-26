#include <bits/stdc++.h>
using namespace std;

int max_oranges(const vector<int> &xs) {
    const int n = xs.size();
    vector<vector<int>> los(n, vector<int>(n, 0));

    int ans = xs[0];
    for (int i = 0; i < n; ++i) {
        for (int j = i; j < n; ++j) {
            if (i == j) {
                los[i][j] = xs[i];
            } else {
                los[i][j] = min(los[i][j - 1], xs[j]);
            }

            ans = max(ans, los[i][j] * (j - i + 1));
        }
    }
    return ans;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n;
    cin >> n;
    vector<int> xs(n);
    for (auto &x : xs) cin >> x;

    cout << max_oranges(xs) << '\n';

    return 0;
}
