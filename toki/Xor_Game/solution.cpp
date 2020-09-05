#include <bits/stdc++.h>
using namespace std;
using ll = long long;

ll max_xor(vector<ll> &xs) {
    const ll intact = accumulate(xs.cbegin() + 1, xs.cend(), xs[0],
                                 [](const ll a, const ll b) { return a ^ b; });

    ll hi = intact;
    ll to_flip = -1;

    for (const ll x : xs) {
        if ((intact ^ x) > hi) {
            hi = intact ^ x;
            to_flip = x;
        }
    }

    if (to_flip == -1) return intact;

    sort(xs.begin(), xs.end());

    ll ans = hi;
    for (const auto x : xs) {
        if (x >= to_flip) break;
        ans = max(hi ^ x, ans);
    }

    return ans;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int sz;
    cin >> sz;
    vector<ll> xs(sz, 0);
    for (auto &x : xs) cin >> x;

    cout << max_xor(xs) << '\n';
    return 0;
}
