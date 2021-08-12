#include <bits/stdc++.h>
using namespace std;

using ll = long long;

constexpr ll mpow(const ll base, const ll exp) {
    if (!exp) return 1;
    if (exp % 2LL) return base * mpow(base, exp - 1);

    const auto q = mpow(base, exp / 2LL);
    return q * q;
}

int kth_digit(const ll k) {
    ll curr = 0;

    for (ll i = 1; i <= 17; ++i) {
        curr += 9LL * mpow(10, i - 1) * i;

        cerr << "curr: " << curr << endl;
    }

    return -1;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int q;
    cin >> q;
    while (q--) {
        ll k;
        cin >> k;
        cout << kth_digit(k) << '\n';
    }

    return 0;
}
