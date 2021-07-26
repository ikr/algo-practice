#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;
using ui = unsigned int;
using vi = vector<int>;
using si = set<int>;
using usi = unordered_set<int>;
using vll = vector<ll>;
static const ll M = 1e9 + 7;

ll solve(const ll n, const ll k) {
    ll ans = n * k / (n - 1);
    if (ans % n == 0) --ans;
    return  ans;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    
    int t;
    cin >> t;
    for (int i = 0; i != t; ++i) {
        ll n, k;
        cin >> n >> k;
        
        cout << solve(n, k) << '\n';
    }

    return 0;
}
