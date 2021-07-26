#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int t;
    cin >> t;
    while (t--) {
        int x, y, n;
        cin >> x >> y >> n;

        if (n % x == y) {
            cout << n << '\n';
        } else {
            const int ans = y < n % x ? n - (n % x - y) : (n - x + y - n % x);
            cout << ans << '\n';
        }
    }

    return 0;
}
