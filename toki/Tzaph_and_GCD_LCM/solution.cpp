#include <bits/stdc++.h>
using namespace std;
using ll = long long;

pair<ll, ll> find_pair(const ll gcd_v, const ll lcm_v) {
    if (lcm_v % gcd_v) return {-1, -1};
    const ll rem = lcm_v / gcd_v;
    if (rem == 1) return {gcd_v, gcd_v};

    const ll lim = sqrt(rem);
    ll best_sum = 1e18;
    ll best_x = -1;
    for (ll x = 1; x <= lim; ++x) {
        if (rem % x) continue;
        const ll y = rem / x;
        if (gcd(x, y) != 1) continue;

        if (x + y < best_sum) {
            best_x = x;
            best_sum = x + y;
        }
    }

    return {gcd_v * best_x, gcd_v * (rem / best_x)};
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    ll gcd_v, lcm_v;
    cin >> gcd_v >> lcm_v;

    const auto [a, b] = find_pair(gcd_v, lcm_v);
    cout << a << ' ' << b << '\n';

    return 0;
}
