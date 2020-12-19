#include <atcoder/math>
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

ll solve(const ll m, const ll s, const ll k) {
    const ll a = k;
    const ll b = m - s;

    const ll d = gcd(a, m);
    if (b % d != 0) return -1;

    if (gcd(a, m) != 1) {
        const ll aa = a / gcd(a, m);
        const ll mm = m / gcd(a, m);
        return ((b * atcoder::inv_mod(aa, mm)) % m) / gcd(a, m);
    }

    return (b * atcoder::inv_mod(a, m)) % m;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int t;
    cin >> t;
    while (t--) {
        ll n, s, k;
        cin >> n >> s >> k;
        cout << solve(n, s, k) << '\n';
    }

    return 0;
}
