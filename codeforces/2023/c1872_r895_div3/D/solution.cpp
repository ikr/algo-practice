#include <bits/stdc++.h>
using namespace std;

using ll = long long;

ll best_sch(const ll n, const ll x, const ll y) {
    if (x == y) return 0;
    const auto ov = n / lcm(x, y);
    const auto xp = n / x - ov;
    const auto yp = n / y - ov;

    const auto A = xp * (n + (n - xp + 1LL)) / 2LL;
    const auto B = yp * (1LL + yp) / 2LL;
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
