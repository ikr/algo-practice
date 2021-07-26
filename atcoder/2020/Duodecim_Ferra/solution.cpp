#include <bits/stdc++.h>
using namespace std;
using ll = long long;

ll count_ways(vector<vector<ll>> &memo, const ll l, const ll parts) {
    if (memo[l][parts] >= 0) return memo[l][parts];

    if (parts > l) {
        memo[l][parts] = 0;
    } else if (parts == 1) {
        memo[l][parts] = 1;
    } else {

        ll ans = 0;

        for (ll i = 1; i <= l - (parts - 1); ++i) {
            ans += count_ways(memo, l - i, parts - 1);
        }

        memo[l][parts] = ans;
    }

    return memo[l][parts];
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int l;
    cin >> l;

    vector<vector<ll>> memo(201, vector<ll>(13, -1));

    cout << count_ways(memo, l, 12) << '\n';
    return 0;
}
