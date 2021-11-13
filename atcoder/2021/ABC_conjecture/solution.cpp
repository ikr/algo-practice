#include <bits/stdc++.h>
using namespace std;

using ll = long long;

ll count_interesting_triples(const ll n) {
    ll ans{};

    for (ll a = 1; a * a * a <= n; ++a) {
        for (ll b = a; a * b * b <= n; ++b) {
            ans += ((n / a) / b) - b + 1;
        }
    }

    return ans;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    ll n;
    cin >> n;

    cout << count_interesting_triples(n) << '\n';
    return 0;
}
