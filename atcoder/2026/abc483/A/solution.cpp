#include <bits/stdc++.h>
using namespace std;

template <typename T> constexpr T div_ceil(const T x, const T y) {
    return x ? (1 + (x - 1) / y) : 0;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int n;
    cin >> n;
    cout << div_ceil(n, 2) << '\n';

    return 0;
}
