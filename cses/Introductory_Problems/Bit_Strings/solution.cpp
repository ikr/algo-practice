#include <bits/stdc++.h>
using namespace std;
using ll = long long;
static const ll M = 1e9 + 7;

ll exp_m(const ll base, const ll power) {
    if (!power) return 1;
    if (power % 2) return base * exp_m(base, power - 1) % M;
    const ll x = exp_m(base, power / 2);
    return x * x % M;
}

ll bit_strings_num(const ll n) {
    return exp_m(2, n);
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    ll n;
    cin >> n;
    cout << bit_strings_num(n) << '\n';
    
    return 0;
}
