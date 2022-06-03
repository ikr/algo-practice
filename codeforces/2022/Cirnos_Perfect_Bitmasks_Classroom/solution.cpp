#include <iostream>
using namespace std;

int min_y(const int x) {
    if (x == 1) return 3;

    const auto z = __builtin_ctz(x);

    if (__builtin_popcount(x) > 1) {
        return (1 << z);
    }

    return (1 << z) | 1;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t;
    cin >> t;
    while (t--) {
        int x;
        cin >> x;

        cout << min_y(x) << '\n';
    }

    return 0;
}
