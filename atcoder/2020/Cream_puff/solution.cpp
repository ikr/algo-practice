#include <bits/stdc++.h>
using namespace std;
using ll = long long;

vector<ll> divisors(const ll x) {
    vector<ll> ans;
    const ll lim = sqrt(x);
    ans.reserve(lim);

    for (ll i = 1; i <= lim; ++i) {
        if (x % i) continue;

        ans.push_back(i);
        const ll p = x / i;
        if (i != p) ans.push_back(p);
    }

    sort(begin(ans), end(ans));
    return ans;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    ll n;
    cin >> n;

    for (const auto x : divisors(n)) cout << x << '\n';
    return 0;
}
