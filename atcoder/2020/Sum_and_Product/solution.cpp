#include <bits/stdc++.h>
using namespace std;
using ll = long long;

bool solve(const ll s, const ll p) {
    const ll lim = sqrt(p);
    for (ll i = 1; i <= lim; ++i) {
        if (p % i) continue;
        const ll j = p / i;
        if (i + j == s) return true;
    }
    return false;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    ll s, p;
    cin >> s >> p;
    cout << (solve(s, p) ? "Yes\n" : "No\n");

    return 0;
}
