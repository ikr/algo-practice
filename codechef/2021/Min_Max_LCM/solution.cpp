#include <bits/stdc++.h>
using namespace std;

using ll = long long;

pair<ll, ll> minmax_lcm(const ll x, const ll k) {
    return {2LL * x, x * k * (x * k - 1LL)};
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t;
    cin >> t;
    while (t--) {
        ll x, k;
        cin >> x >> k;

        const auto [lo, hi] = minmax_lcm(x, k);
        cout << lo << ' ' << hi << '\n';
    }

    return 0;
}
