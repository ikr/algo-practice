#include <bits/stdc++.h>
using namespace std;

using pii = pair<int, int>;
using ll = long long;

ll min_square_area(const vector<pii> &ps) {
    int x_lo = INT_MAX;
    int x_hi = INT_MIN;
    int y_lo = INT_MAX;
    int y_hi = INT_MIN;

    for (const auto &[x, y] : ps) {
        x_lo = min(x_lo, x);
        x_hi = max(x_hi, x);
        y_lo = min(y_lo, y);
        y_hi = max(y_hi, y);
    }

    const ll a = max(x_hi - x_lo, 1);
    const ll b = max(y_hi - y_lo, 1);
    const auto s = max(a, b);
    return s * s;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;

        vector<pii> ps(n);
        for (auto &[x, y] : ps) cin >> x >> y;

        cout << min_square_area(ps) << '\n';
    }

    return 0;
}
