#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using vll = vector<ll>;

vll num_ways(const ll n) {
    vll ans(n, 0);
    if (n > 1) ans[1] = 6;
    if (n > 2) ans[2] = 28;
    
    for (ll k = 4; k <= n; ++k) {
        const ll f = 2 * k - 1;
        const ll fringe = f * (f - 1) / 2 - 2;
        const ll inner = ans[k - 2];
        const ll inner_square = (k - 1) * (k - 1);
        const ll inner_fringe = 7 * (inner_square - 2) + max(0LL, f - 7) * (inner_square - 4);
        
        ans[k - 1] = fringe + inner + inner_fringe;
    }
    
    return ans;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    ll n;
    cin >> n;
    for (const ll x : num_ways(n)) cout << x << '\n';
    
    return 0;
}
