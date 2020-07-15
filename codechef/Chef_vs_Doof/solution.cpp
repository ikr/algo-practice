#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int t;
    cin >> t;
    while (t--) {
        int sz;
        cin >> sz;

        vector<int> xs(sz, 0);
        for (auto &x : xs) cin >> x;

        bool ans = all_of(xs.cbegin(), xs.cend(), [](const auto x) { return x % 2; });
        cout << (ans ? "YES" : "NO") << '\n';
    }

    return 0;
}
