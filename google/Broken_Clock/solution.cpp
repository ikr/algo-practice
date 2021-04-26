#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vll = vector<ll>;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr ll llof(const T x) {
    return static_cast<ll>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

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

static constexpr ll GIG = 1e9;
static constexpr ll ELV = 100LL * GIG;
static constexpr ll M = 432LL * ELV;
using Tri = tuple<ll, ll, ll>;
using Quad = tuple<ll, ll, ll, ll>;

ll mul_mod(const ll x, const ll y) {
    const __int128_t a = x;
    const __int128_t b = y;
    const __int128_t m = M;
    return llof(a * b % m);
}

Quad nanoseconds_to_time(const ll ns) {
    return {ns / GIG / 60LL / 60LL, (ns / GIG / 60LL) % 60LL, (ns / GIG) % 60LL,
            ns % GIG};
}

Quad solve(vll ts) {
    const ll inv_11 = inv_mod(11LL, M);
    const ll inv_719 = inv_mod(719LL, M);

    sort(begin(ts), end(ts));
    do {
        const ll t_h = ts[0];
        const ll t_m = ts[1];
        const ll t_s = ts[2];

        const ll x = mul_mod((t_m - t_h + M) % M, inv_11);
        const ll y = mul_mod((t_s - t_h + M) % M, inv_719);

        if (x == y && x / GIG / 60LL / 60LL < 11) {
            return nanoseconds_to_time(x);
        }
    } while (next_permutation(begin(ts), end(ts)));

    assert(false);
    return {-1, -1, -1, -1};
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t;
    cin >> t;
    for (int i = 1; i <= t; ++i) {
        ll t1, t2, t3;
        cin >> t1 >> t2 >> t3;

        const auto [h, m, s, n] = solve({t1, t2, t3});
        cout << "Case #" << i << ": " << h << ' ' << m << ' ' << s << ' ' << n
             << '\n';
    }

    return 0;
}
