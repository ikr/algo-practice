#include <bits/stdc++.h>
using namespace std;

using ll = long long;

template <typename T> constexpr ll llof(const T x) { return static_cast<ll>(x); }

ll end_coord(const __int128_t x0, const ll n) {
    const ll x0m2 = ((x0 % 2LL) + 2LL) % 2LL;

    if (n == 0) return x0;
    if (n == 1) return x0m2 ? (x0 + 1) : (x0 - 1);

    const auto progr = [&](const __int128_t a) -> __int128_t {
        if (a > n) {
            return 0;
        }

        __int128_t k = (n - a) / 4LL;

        if (k > 0LL) {
            return (k + 1) * ((2 * a + 4 * k) / 2LL);
        }

        return a;
    };

    if (x0m2 == 0) {
        __int128_t d = -1;
        d += progr(2);
        d -= progr(4);
        d += progr(3);
        d -= progr(5);

        return x0 + d;
    }

    __int128_t d = 1;
    d -= progr(2);
    d += progr(4);
    d -= progr(3);
    d += progr(5);

    return x0 + d;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    cout << setprecision(9) << fixed;

    int t;
    cin >> t;
    while (t--) {
        ll x0, n;
        cin >> x0 >> n;
        cout << end_coord(x0, n) << '\n';
    }

    return 0;
}
