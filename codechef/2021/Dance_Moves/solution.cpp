#include <bits/stdc++.h>
using namespace std;

int min_moves(const int x, const int y) {
    if (x >= y) {
        return x - y;
    }

    const int d = y - x;
    assert(d > 0);
    if (d % 2 == 0) return d / 2;

    return (d + 1) / 2 + 1;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t;
    cin >> t;
    while (t--) {
        int x, y;
        cin >> x >> y;

        cout << min_moves(x, y) << '\n';
    }

    return 0;
}
