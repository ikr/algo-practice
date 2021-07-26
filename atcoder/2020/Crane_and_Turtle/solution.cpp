#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int x, y;
    cin >> x >> y;

    const int r = y - 2 * x;
    const int c = x - r / 2;
    const bool ok = r >= 0 && (r % 2 == 0) && c >= 0;
    cout << (ok ? "Yes" : "No") << '\n';

    return 0;
}
