#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int sz;
    cin >> sz;
    vector<int> xs(sz, 0);
    for (auto &x : xs) cin >> x;

    int ans = 0;

    for (int i = 0; i < sz; ++i) {
        const int pos = i + 1;
        const int x = xs[i];

        if (x % 2 && pos % 2) ++ans;
    }

    cout << ans << '\n';

    return 0;
}
