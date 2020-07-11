#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int l, r, d;
    cin >> l >> r >> d;

    int ans = 0;
    for (int i = l; i <= r; ++i) {
        if (i % d == 0) ++ans;
    }

    cout << ans << '\n';
    return 0;
}
