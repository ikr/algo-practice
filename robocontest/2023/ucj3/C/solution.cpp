#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int n, k;
    ll x;
    cin >> n >> x >> k;

    vector<int> ys(n);
    for (auto &y : ys) cin >> y;

    ll ans = x;

    for (int bits = 0; bits < (1 << n); ++bits) {
        if (__builtin_popcount(bits) > k) continue;
        ll cur = x;

        for (int i = 0; i < n; ++i) {
            if (bits & (1 << i)) {
                if (cur >= ys[i]) cur += ys[i];
            }
        }

        ans = max(ans, cur);
    }

    cout << ans << '\n';
    return 0;
}
