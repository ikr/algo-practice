
#include <bits/stdc++.h>
using namespace std;

int solve(const vector<int> &xs) {
    const int n = xs.size();
    int ans = 1;
    bool potential = false;

    for (int i = 1; i < n; ++i) {
        if (xs[i - 1] == xs[i]) {
            potential = true;
        } else {
            ++ans;
            if (potential && xs[i] - xs[i - 1] > 1) {
                ++ans;
                potential = false;
            }
        }
    }

    if (potential) ++ans;
    return ans;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;

        vector<int> xs(n);
        for (auto &x : xs) cin >> x;
        cout << solve(xs) << '\n';
    }

    return 0;
}
