#include <bits/stdc++.h>
using namespace std;
using ll = long long;

ll solve(vector<int> &xs) {
    const int sz = xs.size();
    ll ans = 0;

    for (int i = 1; i < sz; ++i) {
        if (xs[i] < xs[i - 1]) {
            ans += xs[i - 1] - xs[i];
            xs[i] = xs[i - 1];
        }
    }

    return ans;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int sz;
    cin >> sz;
    vector<int> xs(sz, 0);
    for (auto &x : xs) cin >> x;

    cout << solve(xs) << '\n';

    return 0;
}
