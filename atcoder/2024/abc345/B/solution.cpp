#include <bits/stdc++.h>
using namespace std;

using ll = long long;

template <typename T> constexpr T div_ceil(const T x, const T y) {
    return x ? (1 + (x - 1) / y) : 0;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    ll X;
    cin >> X;

    const auto result = X < 0LL ? -(abs(X) / 10LL) : div_ceil(X, 10LL);
    cout << result << '\n';
    return 0;
}
