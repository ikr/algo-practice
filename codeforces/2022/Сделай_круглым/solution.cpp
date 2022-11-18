#include <bits/stdc++.h>
using namespace std;

using ll = long long;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

ll best_round(const ll n, const ll m) {
    ll result = n * m;
    ll B = 1;

    for (int e = 1; e <= 18; ++e) {
        B *= 10;
        const auto g = gcd(n, B);
        const auto k = B / g;

        if (k <= m) {
            const ll hi = m / k;
            result = n * k * hi;
        }
    }

    return result;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t;
    cin >> t;
    while (t--) {
        ll n, m;
        cin >> n >> m;

        cout << best_round(n, m) << '\n';
    }

    return 0;
}
