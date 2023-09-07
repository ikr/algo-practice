#include <bits/stdc++.h>
using namespace std;

template <typename T> constexpr T div_ceil(const T x, const T y) {
    return x ? (1 + (x - 1) / y) : 0;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t;
    cin >> t;
    while (t--) {
        int a, b, c;
        cin >> a >> b >> c;

        const auto ans = div_ceil(abs(a - b), 2 * c);
        cout << ans << '\n';
    }

    return 0;
}
