#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    ll n;
    cin >> n;

    ll p = 1;
    for (ll i = 2; i <= n; ++i) {
        p = lcm(p, i);
    }

    cout << (p + 1) << '\n';
    return 0;
}
