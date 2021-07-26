#include <bits/stdc++.h>

using namespace std;

using ll = long long;

vector<ll> modulo_counts(const ll m, const ll lo, const ll hi) {
    const ll r = abs((lo % m) - (hi % m));
    const ll q = (hi - lo) / m;
    
    vector<ll> ans(m, q);
    
    for (ll i = lo % m; i <= (lo % m) + r; ++i) {
        ++ans[i];
    }
    
    return ans;
}
    
ll solve(const ll a, const ll b, const ll l, const ll r) {
    const ll m1 = min(a, b);
    const ll m2 = max(a, b);
    if (m1 == m2 || l == r) return 0;
    
    ll ans = 0;
    const auto mc = modulo_counts(m1, l, r);
    for (ll i = l; i < l + m1; ++i) {
        if ((i % m2) % m1 != i % m1) ans += mc[i % m1];
    }
    
    return ans;
}

int main() {
    ios_base::sync_with_stdio(0);
	  cin.tie(0);
    
    int T;
    cin >> T;
    
    for (int tc = 0; tc != T; ++tc) {
        ll a, b;
        int q;
        cin >> a >> b >> q;
        
        for (int i = 0; i != q; ++i) {
            ll l, r;
            cin >> l >> r;
            cout << solve(a, b, l, r) << endl;
        }
    }
    
    return 0;
}
