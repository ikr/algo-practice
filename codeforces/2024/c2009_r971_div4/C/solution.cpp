#include <bits/stdc++.h>
using namespace std;

template <typename T> constexpr T div_ceil(const T x, const T y) {
    return x ? (1 + (x - 1) / y) : 0;
}

int min_moves(const int x, const int y, const int k) {
    const auto qx = div_ceil(x, k);
    const auto qy = div_ceil(y, k);

    if (qx == qy) return qx + qy;

    if (qx > qy) return qx * 2 - 1;

    assert(qy > qx);
    return qy * 2;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t;
    cin >> t;
    while (t--) {
        int x, y, k;
        cin >> x >> y >> k;
        cout << min_moves(x, y, k) << '\n';
    }

    return 0;
}
