#include <bits/stdc++.h>
using namespace std;
using ll = long long;
static constexpr ll M = 998244353;

namespace internal {
constexpr ll safe_mod(ll x, const ll m) {
    x %= m;
    if (x < 0) x += m;
    return x;
}

constexpr pair<ll, ll> inv_gcd(ll a, const ll b) {
    a = safe_mod(a, b);
    if (a == 0) return {b, 0};

    ll s = b, t = a;
    ll m0 = 0, m1 = 1;

    while (t) {
        const ll u = s / t;
        s -= t * u;
        m0 -= m1 * u;

        auto tmp = s;
        s = t;
        t = tmp;
        tmp = m0;
        m0 = m1;
        m1 = tmp;
    }

    if (m0 < 0) m0 += b / s;
    return {s, m0};
}
} // namespace internal

constexpr ll inv_mod(const ll x, const ll m) {
    assert(1 <= m);
    const auto z = internal::inv_gcd(x, m);
    assert(z.first == 1);
    return z.second;
}

ll factorial(const ll x) {
    assert(x >= 0);
    if (x <= 1) return 1;

    ll ans = 2;
    for (ll i = 3; i <= x; ++i) {
        ans *= i;
        ans %= M;
    }

    return ans;
}

ll product_of_range(const ll a, const ll b) {
    ll ans = 1;
    for (ll x = a; x <= b; ++x) {
        ans *= x;
        ans %= M;
    }
    return ans;
}

ll combinations(const ll n, const ll k) {
    assert(k <= n);
    const ll r = n - k;
    const ll ans = r < k
                       ? product_of_range(k + 1, n) * inv_mod(factorial(r), M)
                       : product_of_range(r + 1, n) * inv_mod(factorial(k), M);
    return ans % M;
}

ll num_grids(const ll n, const ll m) {
    const ll hi = n * m / 2;
    const ll nm = n * m;
    ll ans = 0;

    for (ll k = 0; k <= hi; ++k) {
        ans += combinations(nm, k * 2LL);
        ans %= M;
    }

    return ans;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n, m;
    cin >> n >> m;
    cout << num_grids(n, m) << '\n';

    return 0;
}
