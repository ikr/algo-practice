#include <bits/stdc++.h>
using namespace std;
using ll = long long;
constexpr ll M = 1e9 + 7;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int sz;
    cin >> sz;
    vector<int> xs(sz, 0);
    for (auto &x : xs) cin >> x;

    ll ans = 0;
    ll s = 0;

    for (int i = sz - 2; i >= 0; --i) {
        s += xs[i + 1];
        s %= M;

        ans += xs[i] * s;
        ans %= M;
    }

    cout << ans << '\n';

    return 0;
}
