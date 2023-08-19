#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t;
    cin >> t;
    while (t--) {
        int n;
        ll x;
        cin >> n >> x;

        vector<ll> ys(n);
        for (auto &y : ys) cin >> y;

        for (const auto y : ys) {
            if (x >= y) {
                x += y;
            }
        }

        cout << x << '\n';
    }

    return 0;
}
