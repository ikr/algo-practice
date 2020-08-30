#include <bits/stdc++.h>
using namespace std;

bool can_hit_all(const vector<int> &xs, const int d, const double c) {
    const int n = xs.size();
    double p = xs[0] + c;

    for (int i = 1; i < n; ++i) {
        p = max(p, static_cast<double>(xs[i]));
        if (p > xs[i] + d) return false;
        p += c;
    }

    return true;
}

double solve(vector<int> xs, const int d) {
    sort(begin(xs), end(xs));

    double lo = 0;
    double hi = 1e10;
    double mid = -1;

    for (int i = 0; i < 100; ++i) {
        mid = lo + (hi - lo) / 2.0;

        if (can_hit_all(xs, d, mid))
            lo = mid;
        else
            hi = mid;
    }

    return mid;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout << setprecision(6) << fixed;

    int t;
    cin >> t;
    while (t--) {
        int n, d;
        cin >> n >> d;
        vector<int> xs(n, 0);
        for (auto &x : xs) cin >> x;
        cout << solve(xs, d) << '\n';
    }

    return 0;
}
