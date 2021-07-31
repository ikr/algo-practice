#include <bits/stdc++.h>
using namespace std;

using ll = long long;

template <typename T> constexpr T div_ceil(const T x, const T y) {
    return x ? (1 + (x - 1) / y) : 0;
}

static constexpr int LIM = 240;

ll min_minutes(const ll n) {
    if (n <= 6LL) return 15;
    if (n <= 8LL) return 20;
    if (n <= 10LL) return 25;

    if (n % 2LL) {
        return 15LL + min_minutes(n - 5LL);
    }

    return (n / 2LL) * 5LL;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t;
    cin >> t;
    while (t--) {
        ll n;
        cin >> n;
        cout << min_minutes(n) << '\n';
    }

    return 0;
}
