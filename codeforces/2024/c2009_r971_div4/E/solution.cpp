#include <bits/stdc++.h>
using namespace std;

using ll = long long;

ll xval(const ll n, const ll k, const ll i) {
    assert(i >= 0);
    assert(i < n);

    const auto A = (i + 1LL) * (k + k + i) / 2LL;
    const auto B = (n - 1 - i) * (k + i + 1 + k + n - 1) / 2LL;
    return abs(A - B);
}

ll min_xval(const ll n, const ll k) {
    ll l{};
    ll r{n - 1};

    while (r - l >= 3) {
        const auto m1 = l + (r - l) / 3LL;
        const auto m2 = r - (r - l) / 3LL;

        const auto fm1 = xval(n, k, m1);
        const auto fm2 = xval(n, k, m2);

        if (fm1 < fm2) {
            r = m2;
        } else if (fm1 > fm2) {
            l = m1;
        } else {
            l = m1;
            r = m2;
        }
    }

    ll result{LONG_LONG_MAX};
    for (ll i = l; i <= r; ++i) {
        result = min(result, xval(n, k, i));
    }
    return result;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t;
    cin >> t;
    while (t--) {
        ll n, k;
        cin >> n >> k;
        cout << min_xval(n, k) << '\n';
    }

    return 0;
}
