#include <bits/stdc++.h>
using namespace std;
using ll = long long;
static constexpr ll M = 1e9 + 7;

constexpr ll pow_mod(const ll base, const ll exp, const ll m) {
    if (!exp) return 1;
    if (exp % 2) return (base * pow_mod(base, exp - 1, m)) % m;
    const ll q = pow_mod(base, exp / 2, m);
    return (q * q) % m;
}


template <typename T> constexpr tuple<T, T, T> extended_gcd(const T a, const T b) {
    auto [old_r, r] = pair{a, b};
    auto [old_s, s] = pair<T, T>{1, 0};
    auto [old_t, t] = pair<T, T>{0, 1};

    while (r) {
        const T quotient = old_r / r;
        tie(old_r, r) = pair{r, old_r - quotient * r};
        tie(old_s, s) = pair{s, old_s - quotient * s};
        tie(old_t, t) = pair{t, old_t - quotient * t};
    }

    return {old_s, old_t, old_r};
}

template <typename T> constexpr T inv_mod(const T x, const T m) {
    return (get<0>(extended_gcd(x, m)) + m) % m;
}

constexpr ll sum_1_to_n_mod(const ll n, const ll m) {
    ll ans = n * (n + 1);
    ans %= m;
    ans *= inv_mod(2LL, m);
    ans %= m;
    return ans;
}

ll sum_of_sum_of_divisors(const ll x) {
    ll ans = 0;

    for (ll lo = 1; lo <= x;) {
        const ll q = x / lo;
        const ll hi = x / q;

        ll to_add = sum_1_to_n_mod(hi, M) - sum_1_to_n_mod(lo - 1, M);
        to_add += M;
        to_add %= M;

        to_add *= (q % M);
        to_add %= M;

        ans += to_add;
        ans %= M;

        lo = hi + 1;
    }

    return ans;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    ll x;
    cin >> x;
    cout << sum_of_sum_of_divisors(x) << '\n';

    return 0;
}
