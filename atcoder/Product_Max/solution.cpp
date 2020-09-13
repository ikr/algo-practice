#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    ll a, b, c, d;
    cin >> a >> b >> c >> d;

    const ll ans = max({a * c, a * d, b * c, b * d});
    cout << ans << '\n';

    return 0;
}
