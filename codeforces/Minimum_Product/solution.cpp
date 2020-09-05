#include <bits/stdc++.h>
using namespace std;
using ll = long long;

ll min_product(const ll a, const ll b, const ll x, const ll y, const ll n) {
    const ll o1 = [&]() {
        ll budget = n;
        const ll da = min(a - x, budget);
        budget -= da;

        const ll db = min(b - y, budget);
        return (a - da) * (b - db);
    }();

    const ll o2 = [&]() {
        ll budget = n;
        const ll db = min(b - y, budget);
        budget -= db;

        const ll da = min(a - x, budget);
        return (a - da) * (b - db);
    }();

    return min(o1, o2);
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int t;
    cin >> t;
    while (t--) {
        ll a, b, x, y, n;
        cin >> a >> b >> x >> y >> n;
        cout << min_product(a, b, x, y, n) << '\n';
    }

    return 0;
}
