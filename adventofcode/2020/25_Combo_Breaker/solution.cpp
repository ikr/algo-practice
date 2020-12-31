#include <bits/stdc++.h>
using namespace std;
using ll = long long;
static constexpr ll M = 20201227;

constexpr ll pow_mod(const ll base, const ll exp, const ll m) {
    if (!exp) return 1;
    if (exp % 2) return (base * pow_mod(base, exp - 1, m)) % m;
    const ll q = pow_mod(base, exp / 2, m);
    return (q * q) % m;
}

ll log7_mod(const ll y0) {
    for (ll i = 0, y = 1;; ++i) {
        if (y == y0) return i;
        y *= 7;
        y %= M;
    }

    return 0;
}

int main() {
    ll cpk, dpk;
    cin >> cpk >> dpk;

    const ll x = log7_mod(cpk);
    const ll y = log7_mod(dpk);

    cout << pow_mod(pow_mod(7, x, M), y, M) << '\n';

    return 0;
}
