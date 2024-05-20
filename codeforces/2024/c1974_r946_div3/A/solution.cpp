#include <bits/stdc++.h>
using namespace std;

template <typename T> constexpr T div_ceil(const T x, const T y) {
    return x ? (1 + (x - 1) / y) : 0;
}

int min_screens(int x, const int y) {
    const auto screens_for_y = div_ceil(y, 2);
    const auto one_slots_in_y_screens = 15 * screens_for_y - 4 * y;
    const auto d = min(x, one_slots_in_y_screens);
    x -= d;
    if (!x) return screens_for_y;
    return screens_for_y + div_ceil(x, 15);
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t;
    cin >> t;
    while (t--) {
        int x, y;
        cin >> x >> y;
        cout << min_screens(x, y) << '\n';
    }

    return 0;
}
