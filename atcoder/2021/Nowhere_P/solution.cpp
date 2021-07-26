#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vi = vector<int>;
using vvi = vector<vi>;
using pii = pair<int, int>;
using vll = vector<ll>;
using vvll = vector<vll>;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}
template <typename T> constexpr ll llof(const T x) {
    return static_cast<ll>(x);
}
template <typename T> constexpr double doof(const T x) {
    return static_cast<double>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

static constexpr ll M = 1e9 + 7;

constexpr ll pow_mod(const ll base, const ll exp, const ll m) {
    if (!exp) return 1;
    if (exp % 2) return (base * pow_mod(base, exp - 1, m)) % m;
    const ll q = pow_mod(base, exp / 2, m);
    return (q * q) % m;
}

ll num_very_good(const ll n, const ll p) {
    return ((p - 1) * pow_mod(p - 2, n - 1, M)) % M;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    cout << setprecision(9) << fixed;

    ll n, p;
    cin >> n >> p;

    cout << num_very_good(n, p) << '\n';
    return 0;
}
