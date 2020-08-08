#include <bits/stdc++.h>
using namespace std;
using ll = long long;

static constexpr ll M = 1e9 + 7;

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

constexpr ll mmul(const ll x, const ll y) { return (x * y) % M; }

template <typename T> constexpr T ceil_div(const T x, const T y) {
    return x % y ? x / y + 1 : x / y;
}

ll solve(const vector<ll> &xs) {
    const int sz = xs.size();
    ll prod = accumulate(xs.cbegin(), xs.cbegin() + sz / 2, 1, mmul);
    ll ans = prod;

    for (int i = 1; i <= ceil_div(sz, 2); ++i) {
        prod *= mod_inverse(xs[i - 1], M);
        prod %= M;

        prod *= xs[i + sz / 2 - 1];
        prod %= M;

        ans += prod;
        ans %= M;
    }

    return ans;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int sz = 0;
    cin >> sz;
    vector<ll> xs(sz, 0);
    for (auto &x : xs) cin >> x;

    cout << solve(xs) << '\n';

    return 0;
}
