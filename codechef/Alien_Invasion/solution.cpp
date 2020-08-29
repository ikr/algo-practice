#include <algorithm>
#include <bits/stdc++.h>
using namespace std;

double solve(const vector<int> &xs, const int d) {
    const int n = xs.size();
    const auto [lo, hi] = minmax_element(cbegin(xs), cend(xs));

    const double span = *hi - *lo;
    return (span + d) / n;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.precision(15);

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
