#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t;
    cin >> t;
    while (t--) {
        int x, y, z;
        cin >> x >> y >> z;

        const auto ans = [&]() -> int {
            if (z >= x + y) return 2;
            if (z >= x) return 1;
            return 0;
        }();

        cout << ans << '\n';
    }

    return 0;
}
