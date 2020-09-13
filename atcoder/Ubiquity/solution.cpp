#include <bits/stdc++.h>
using namespace std;

using ll = long long;
constexpr ll M = 1e9 + 7;

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

vector<int> precompute_fact(const int n) {
    vector<int> ans(n + 1, 1);
    int curr = 1;
    for (ll i = 2; i <= n; ++i) {
        ans[i] = (ans[i - 1] * i) % M;
    }
    return ans;
}

int combinations(const vector<int> &fact, const int n, const int k) {
    return (fact[n] * mod_inverse(static_cast<ll>(fact[k] * fact[n - k]), M)) %
           M;
}

int solve(const ll n) {
    if (n < 2) return 0;
    if (n == 2) return 2;

    ll ans = 1;

    return ans;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n;
    cin >> n;
    cout << solve(n) << '\n';

    return 0;
}
