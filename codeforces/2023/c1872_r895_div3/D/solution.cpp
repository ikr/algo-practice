#include <bits/stdc++.h>
using namespace std;

using ll = long long;

ll best_sch(const ll n, const ll x, const ll y) {
    const auto xp = n / x;
    const auto yp = n / y;
    const auto overlap = n / lcm(x, y);

    const auto A = xp * (n + (n - xp + 1LL)) / 2LL;
    const auto B = (yp + overlap) * (1LL + yp + overlap) / 2LL;
    return A - B;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t;
    cin >> t;
    while (t--) {
        ll n, x, y;
        cin >> n >> x >> y;

        cout << best_sch(n, x, y) << '\n';
    }

    return 0;
}
