#include <bits/stdc++.h>
using namespace std;

using ll = long long;

template <typename T> constexpr T div_ceil(const T x, const T y) {
    return x ? (1 + (x - 1) / y) : 0;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    ll x;
    cin >> x;

    cout << div_ceil(x, 2LL) << '\n';
    return 0;
}
