#include <bits/stdc++.h>
using namespace std;
using vi = vector<int>;
using ll = long long;

ll max_total_comfort(vi xs) {
    sort(xs.begin(), xs.end(), greater<int>{});
    const int sz = xs.size();

    if (sz == 2) return max(xs[0], xs[1]);
    assert(sz >= 3);

    int l = xs[1];
    int r = xs[2];

    ll ans = xs[0] + xs[1];

    for (int i = 3; i < sz; ++i) {
        const int x = xs[i];

        if (l >= r) {
            ans += l;
            l = x;
            continue;
        }

        ans += r;
        r = x;
    }

    return ans;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int t;
    cin >> t;
    vi xs(t, 0);
    for (auto &x : xs) cin >> x;

    cout << max_total_comfort(xs) << '\n';

    return 0;
}
