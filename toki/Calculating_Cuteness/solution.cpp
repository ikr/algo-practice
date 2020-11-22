#include <bits/stdc++.h>
using namespace std;
using ll = long long;
static constexpr ll M = 1e9 + 7;
static constexpr ll LIM = 1001;

template <typename T> tuple<T, T, T> extended_gcd(const T a, const T b) {
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

template <typename T> T mod_inverse(const T x, const T m) {
    return (get<0>(extended_gcd(x, m)) + m) % m;
}

vector<ll> gather_fact() {
    vector<ll> ans(LIM, 1);
    for (ll i = 2; i < LIM; ++i) {
        ans[i] = (ans[i - 1] * i) % M;
    }
    return ans;
}

ll combinations(const vector<ll> &fact, const ll n, const ll k) {
    const ll q = (fact[k] * fact[n - k]) % M;
    return (fact[n] * mod_inverse(q, M));
}

ll mpow(const ll x, const int p) {
    if (p == 0) return 1;
    if (p % 2) return (x * mpow(x, p - 1)) % M;
    const ll sq = mpow(x, p / 2);
    return (sq * sq) % M;
}

ll cute_count(const ll n, const ll m) {
    if (n == 1) return 1;
    if (m == 1) return 0;

    const auto fact = gather_fact();
    ll ans = 0;

    for (ll k = 1; k < n; ++k) {
        const ll a = combinations(fact, n, k);
        const ll b = mpow(m - 1, n - k);
        ans += (a * b) % M;
    }

    return ans;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    ll n, m;
    cin >> n >> m;
    cout << cute_count(n, m) << '\n';

    return 0;
}
