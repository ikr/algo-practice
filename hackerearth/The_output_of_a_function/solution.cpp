#include <bits/stdc++.h>
using namespace std;
using ll = long long;

constexpr ll M = 1e9 + 7;

ll fact(const ll x) {
    ll ans = 1;

    for (int i = 2; i <= x; ++i) {
        ans *= i;
        ans %= M;
    }

    return ans;
}

ll pow(const ll base, const ll power) {
    if (!power) return 1;
    if (power % 2) return (base * pow(base, power - 1)) % M;

    const ll sq = pow(base, power / 2);
    return (sq * sq) % M;
}

ll solve(const int p, const int q, const int r) {
    ll ans = 0;
    for (int i = 0; i <= p; i++) {
        ll temp = 0;

        for (int j = 1; j <= q; j++) {
            const ll ta = pow(r, i); // where pow() is the power function
            const ll tb = ((ta - 1) * ta) % M;
            temp += pow(tb, j);
        }

        ll temp2 = fact(p) * ((fact(p - i) * fact(i)) %
                              M); // where fact() is the factorial function

        temp2 %= M;

        if (i & 1)
            ans -= (temp * temp2) % M;
        else
            ans += (temp * temp2) % M;
    }

    return ans % M;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int t;
    cin >> t;
    while (t--) {
        int p, q, r;
        cin >> p >> q >> r;

        cout << solve(p, q, r) << '\n';
    }

    return 0;
}
