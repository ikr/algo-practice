#include <bits/stdc++.h>
using namespace std;
using vi = vector<int>;
using ll = long long;

ll max_total_comfort(vi xs) {
    sort(xs.begin(), xs.end(), greater<int>{});
    const int sz = xs.size();

    ll ans = xs[0];
    for (int i = 1; i < sz / 2; ++i) ans += 2 * xs[i];
    if (sz % 2) ans += xs[sz / 2];
    return ans;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int sz;
    cin >> sz;
    vi xs(sz, 0);
    for (auto &x : xs) cin >> x;

    cout << max_total_comfort(xs) << '\n';

    return 0;
}
