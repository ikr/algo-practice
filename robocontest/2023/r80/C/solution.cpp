#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t;
    cin >> t;
    while (t--) {
        ll a, b, c;
        cin >> a >> b >> c;

        const auto g = gcd(a, b);
        const auto yes = (c % g) == 0;
        cout << (yes ? "Yes" : "No") << '\n';
    }

    return 0;
}
