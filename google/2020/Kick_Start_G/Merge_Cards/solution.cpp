#include <bits/stdc++.h>
using namespace std;

double solve(const vector<double> &xs) {
    const int n = xs.size();
    vector<vector<double>> memo(n, vector<double>(n, -1));
    function<double(int, int)> ev_merges;

    ev_merges = [&](const int l, const int r) {
        if (memo[l][r] >= 0.0) return memo[l][r];

        double ans = 0;

        if (l > 0) {
            ans += 1.0 + ev_merges(l - 1, r);
        }

        if (l > 1) {
            ans += (l - 1) * ev_merges(l - 1, r);
        }

        if (r > 0) {
            ans += 1.0 + ev_merges(l, r - 1);
        }

        if (r > 1) {
            ans += (r - 1) * ev_merges(l, r - 1);
        }

        if (r + l > 0) ans /= static_cast<double>(r + l);
        memo[l][r] = ans;
        return ans;
    };

    double ans = 0;
    for (int i = 0; i < n; ++i) {
        ans += xs[i] * ev_merges(i, n - i - 1);
    }
    return ans;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout << setprecision(7) << fixed;

    int t;
    cin >> t;
    for (int i = 1; i <= t; ++i) {
        int n;
        cin >> n;
        vector<double> xs(n, 0);
        for (auto &x : xs) cin >> x;

        cout << "Case #" << i << ": " << solve(xs) << '\n';
    }

    return 0;
}
