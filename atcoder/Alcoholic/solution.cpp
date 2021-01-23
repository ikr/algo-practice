#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int drunk_idx(const ll x, const vector<pair<ll, ll>> &ps) {
    const int n = ps.size();
    ll curr = 0;

    for (int i = 0; i < n; ++i) {
        const auto [v, p] = ps[i];
        const ll d = v * p;
        curr += d;
        if (curr > x) return i;
    }

    return -1;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n, x;
    cin >> n >> x;
    x *= 100LL;

    vector<pair<ll, ll>> ps(n);
    for (auto &[v, p] : ps) cin >> v >> p;

    const int ans = drunk_idx(x, ps);
    cout << (ans >= 0 ? ans + 1 : -1) << '\n';

    return 0;
}
