#include <bits/stdc++.h>
using namespace std;

template <typename T1, typename T2>
ostream &operator<<(ostream &os, const pair<T1, T2> &x) {
    os << x.first << ' ' << x.second;
    return os;
}

using ll = long long;
using pll = pair<ll, ll>;

template <typename T> constexpr T div_ceil(const T x, const T y) {
    return x ? (1 + (x - 1) / y) : 0;
}

pll find_x_and_y(const ll a, const ll b, const ll c, const ll d) {
    for (ll x = a + 1; x <= c; ++x) {
        const auto g = gcd(x, a * b);

        const auto lo = g * b / (a * b);
        const auto hi = g * d / (a * b);

        if (lo + 1LL <= hi) {
            const auto k = lo + 1LL;
            const auto y = k * a * b / g;
            return {x, y};
        }
    }

    return {-1, -1};
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t;
    cin >> t;
    while (t--) {
        ll a, b, c, d;
        cin >> a >> b >> c >> d;

        cout << find_x_and_y(a, b, c, d) << '\n';
    }

    return 0;
}
