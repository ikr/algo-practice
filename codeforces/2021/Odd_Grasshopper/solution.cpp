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

template <typename T> constexpr T div_ceil(const T x, const T y) {
    return x ? (1 + (x - 1) / y) : 0;
}

ll end_coord(const ll x0, const ll n) {
    const ll x0m2 = ((x0 % 2LL) + 2LL) % 2LL;

    if (n == 0) return x0;
    if (n == 1) return x0m2 ? (x0 + 1) : (x0 - 1);

    const auto progr = [&](const ll a) -> ll {
        if (a > n) {
            return 0;
        }

        ll k = (n - a) / 4LL;

        if (k > 0) {
            return (k + 1) * ((2 * a + 4 * k) / 2LL);
        }

        return a;
    };

    if (x0m2 == 0) {
        ll d = -1;
        d += progr(2);
        d -= progr(4);
        d += progr(3);
        d -= progr(5);

        return x0 + d;
    }

    ll d = 1;
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
