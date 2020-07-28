#include <bits/stdc++.h>
using namespace std;
using ll = long long;
static const ll M = 1e9 + 7;

ll expm(const ll a, const ll b) {
    if (!b) return 1;
    if (b % 2) return (a * expm(a, b - 1)) % M;
    const ll sq = expm(a, b / 2);
    return (sq * sq) % M;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int t;
    cin >> t;
    while (t--) {
        ll a, b;
        cin >> a >> b;
        cout << expm(a, b) << '\n';
    }

    return 0;
}
