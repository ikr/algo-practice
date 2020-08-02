#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    ll N, D;
    cin >> N >> D;
    vector<pair<ll, ll>> xys(N, {0, 0});
    for (auto &xy : xys) cin >> xy.first >> xy.second;

    const ll d2 = D * D;
    int ans = 0;
    for (const auto [x, y] : xys) {
        const ll p2 = x * x + y * y;
        if (p2 <= d2) ++ans;
    }

    cout << ans << '\n';

    return 0;
}
