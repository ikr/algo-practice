#include <bits/stdc++.h>

using namespace std;

using ll = long long;

pair<ll, ll> piles(const ll n) {
    if (n == 2) return {2, 4};
    
    ll p1 = 0;
    ll p2 = (1 << n) + 2;
    
    const ll m = n / 2;

    for (ll i = 2; i <= m - 1; ++i) {
        p2 += (1 << i);
    }
    
    for (ll i = m + 2; i < n; ++i) {
        p1 += (1 << i);
    }
    
    p1 += (1 << m) + (1 << (m + 1));
    
    return {p1, p2};
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    
    int t;
    cin >> t;
    
    for (int i = 0; i != t; ++i) {
        ll n;
        cin >> n;

        const auto [a, b] = piles(n);
        cout << abs(a - b) << endl;
    }
    
    return 0;
}
