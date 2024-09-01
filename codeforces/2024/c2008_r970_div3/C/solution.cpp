#include <bits/stdc++.h>
using namespace std;

using ll = long long;

ll max_good_length(const ll l, const ll r) {
    if (l == r) return 1;

    const auto d = r - l;
    const auto h0 = d * (d + 1LL) / 2LL;
    if (l + h0 <= r) return d + 1;

    ll lo = 0;
    ll hi = d;

    while (lo + 1 < hi) {
        const auto mid = midpoint(lo, hi);
        const auto h = mid * (mid + 1LL) / 2LL;
        if (l + h <= r) {
            lo = mid;
        } else {
            hi = mid;
        }
    }

    return lo + 1;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t;
    cin >> t;
    while (t--) {
        ll l, r;
        cin >> l >> r;
        cout << max_good_length(l, r) << '\n';
    }

    return 0;
}
