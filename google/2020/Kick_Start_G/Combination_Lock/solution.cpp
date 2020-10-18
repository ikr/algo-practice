#include <bits/stdc++.h>
using namespace std;
using ll = long long;

ll diff(const ll m, const ll x, const ll y) {
    const auto a = min(x, y);
    const auto b = max(x, y);
    return min(b - a, a + m - b);
}

ll solve(const int n, const vector<int> &xs) {
    ll ans = 1e18;

    for (const auto y : xs) {
        ll candidate = 0;
        for (const auto x : xs) {
            candidate += diff(n, x, y);
        }

        ans = min(ans, candidate);
    }

    return ans;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int t;
    cin >> t;
    for (int i = 1; i <= t; ++i) {
        int w, n;
        cin >> w >> n;
        vector<int> xs(w, 0);
        for (auto &x : xs) {
            cin >> x;
            --x;
        }

        cout << "Case #" << i << ": " << solve(n, xs) << '\n';
    }

    return 0;
}
