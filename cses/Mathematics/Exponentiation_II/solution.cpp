#include <bits/stdc++.h>
using namespace std;
using ll = long long;
static constexpr ll M = 1e9 + 7;

ll mpow(const ll base, const ll exp) {
    if (!exp) return 1;
    if (exp % 2) return (base * mpow(base, exp - 1)) % M;
    const ll q = mpow(base, exp / 2);
    return (q * q) % M;
}

ll mpow_abc(const ll a, const ll b, const ll c) {
    if (!c) return a;
    if (c % 2) return mpow_abc(mpow(a, b), b, c - 1);
    const ll q = mpow_abc(a, b, c / 2);
    return mpow_abc(q, b, c / 2);
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
