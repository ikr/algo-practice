#include <cmath>
#include <iostream>
using namespace std;

using HugeUInt = __uint128_t;
using ll = long long;

template <typename T> constexpr HugeUInt hoof(const T x) {
    return static_cast<HugeUInt>(x);
}

ll num_minutes(const ll a, const ll x, const ll b) {
    if (a >= b) return 0;

    ll y = a;
    int k = 1;
    while (hoof(y) * hoof(x + 1) < hoof(b)) {
        ++k;
        y *= (x + 1);
    }
    return k;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    ll a, b, x;
    cin >> a >> b >> x;

    cout << num_minutes(a, x, b) << '\n';
    return 0;
}
