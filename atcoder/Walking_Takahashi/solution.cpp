#include <bits/stdc++.h>
using namespace std;
using ll = long long;

ll min_dest_abs(const ll x, const ll k, const ll d) {
    if (!k) return x;

    if (d <= x) {
        const ll q = min(x / d, k);
        return min_dest_abs(x - q * d, k - q, d);
    }

    assert(d > x);
    return k % 2 ? d - x : x;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    ll x, k, d;
    cin >> x >> k >> d;
    cout << min_dest_abs(abs(x), k, d) << '\n';

    return 0;
}
