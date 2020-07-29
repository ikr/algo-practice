#include <bits/stdc++.h>
using namespace std;
using ll = long long;

pair<ll, ll> solve(const ll l, const ll r) {
    if (r % l == 0) return {l, r};
    return l * 2 <= r ? pair{l, l * 2} : pair{-1LL, -1LL};
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int t;
    cin >> t;
    while (t--) {
        int l, r;
        cin >> l >> r;

        auto [x, y] = solve(l, r);
        cout << x << ' ' << y << '\n';
    }

    return 0;
}
