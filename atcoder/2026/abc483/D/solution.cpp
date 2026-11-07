#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using pll = pair<ll, ll>;

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int n;
    cin >> n;

    vector<ll> xs(n);

    for (auto &x : xs) {
        cin >> x;
    }

    // dp[i][j] i: 0/1 -- flipped already? j: up to index j in xs

    for (int i = 1; i != n; ++i) {
    }

    return 0;
}
