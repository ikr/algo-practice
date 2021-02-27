#include <bits/stdc++.h>
using namespace std;
using ll = long long;
static constexpr ll LIM = 1e10;

constexpr ll mpow(const ll base, const ll exp) {
    if (!exp) return 1;
    if (exp % 2LL) return base * mpow(base, exp - 1LL);
    const ll q = mpow(base, exp / 2LL);
    return (q * q);
}

set<ll> all_powers() {
    set<ll> ans;

    for (ll a = 2LL; log2(a) * 2.0 < log2(2.0 * LIM); ++a) {
        for (ll b = 2LL; b * log2(a) < log2(2.0 * LIM); ++b) {
            const ll c = mpow(a, b);
            assert(c > 0LL);
            ans.insert(c);
        }
    }

    return ans;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    ll n;
    cin >> n;

    const auto ps = all_powers();

    const auto it = ps.upper_bound(n);
    const ll c = distance(cbegin(ps), it);
    const ll ans = n - c;

    cout << ans << '\n';
    return 0;
}
