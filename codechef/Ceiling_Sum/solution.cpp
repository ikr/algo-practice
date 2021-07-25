#include <bits/stdc++.h>
using namespace std;

using ll = long long;

constexpr ll sign(const ll x) {
    if (x == 0LL) return 0LL;
    return x < 0LL ? -1LL : 1LL;
}

constexpr ll div_ceil(const ll x, const ll y) {
    if (x % y == 0LL) return x / y;
    const bool positive = sign(x) == sign(y);
    return positive ? (abs(x) / abs(y) + 1) : -(abs(x) / abs(y));
}

ll f_val(const ll a, const ll b, const ll x) {
    return div_ceil(b - x, 2LL) + div_ceil(x - a, 2LL);
}

ll optimal_f(const ll a, const ll b) {
    if (a == b) return 0;
    if (a < b) return f_val(a, b, a + 1);
    return f_val(a, b, a - 1);
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    assert(div_ceil(-1, 2) == 0LL);
    assert(div_ceil(-3, 2) == -1LL);
    assert(div_ceil(5, 2) == 3LL);

    int t;
    cin >> t;
    while (t--) {
        ll a, b;
        cin >> a >> b;
        cout << optimal_f(a, b) << '\n';
    }

    return 0;
}
