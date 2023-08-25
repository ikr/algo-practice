#include <bits/stdc++.h>
using namespace std;

using ll = long long;
constexpr ll x_choose_2(const ll x) { return (x * (x - 1LL)) / 2LL; }

ll min_balls(ll m) {
    ll lo = 1;
    ll hi = 2648956421LL;

    while (lo + 1 < hi) {
        const auto x = midpoint(lo, hi);
        if (x_choose_2(x) <= m) {
            lo = x;
        } else {
            hi = x;
        }
    }
    if (x_choose_2(lo) == m) return lo;
    return m - x_choose_2(lo) + lo;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t;
    cin >> t;
    while (t--) {
        ll m;
        cin >> m;

        cout << min_balls(m) << '\n';
    }

    return 0;
}
