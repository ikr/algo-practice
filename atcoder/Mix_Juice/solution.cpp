#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int sz, k;
    cin >> sz >> k;
    vector<int> xs(sz, 0);
    for (auto &x : xs) cin >> x;
    sort(xs.begin(), xs.end());
    int ans = accumulate(xs.cbegin(), xs.cbegin() + k, 0);

    cout << ans << '\n';
    return 0;
}
