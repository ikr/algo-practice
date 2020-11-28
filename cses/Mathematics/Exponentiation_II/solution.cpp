#include <bits/stdc++.h>
using namespace std;
using ll = long long;
static constexpr ll M = 1e9 + 7;
static constexpr ll PHI = 1e9 + 6;

ll mpow_mod(const ll base, const ll exp, const ll m) {
    if (!exp) return 1;
    if (exp % 2) return (base * mpow_mod(base, exp - 1, m)) % m;
    const ll q = mpow_mod(base, exp / 2, m);
    return (q * q) % m;
}

ll mpow_abc(const ll a, const ll b, const ll c) {
    return mpow_mod(a, mpow_mod(b, c, PHI), M);
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int t;
    cin >> t;
    while (t--) {
        ll a, b, c;
        cin >> a >> b >> c;
        cout << mpow_abc(a, b, c) << '\n';
    }

    return 0;
}
