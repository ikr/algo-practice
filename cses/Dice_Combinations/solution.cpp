#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using vll = vector<ll>;
static const ll M = 1e9 + 7;
 
ll solve(const ll x) {
    vll dp(x + 1, 0);
    dp[0] = 1;
    for (ll i = 1; i <= x; ++i) {
        for (ll d = i - 1; d >= max(0LL, i - 6); --d) {
            dp[i] += dp[d];
            dp[i] %= M;
        }
    }
    return dp.back();
}
 
int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
 
    int x;
    cin >> x;
    cout << solve(x) << '\n';
    return 0;
}
