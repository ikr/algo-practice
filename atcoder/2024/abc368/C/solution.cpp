#include <bits/stdc++.h>
using namespace std;

using ll = long long;

ll turns_to_take_down(const ll t, const ll h) {
    if (h <= 0) return 0;
    const auto tr = t % 3LL;
    if (tr) {
        const auto dt = min(h, 3 - tr);
        return dt + turns_to_take_down(t + dt, h - dt);
    }

    const auto k = h / 5LL;
    const auto r = h % 5LL;

    switch (r) {
    case 0:
        return k * 3;
    case 1:
        return k * 3 + 1;
    case 2:
        return k * 3 + 1;
    case 3:
        return k * 3 + 1;
    default:
        assert(r == 4);
        return k * 3 + 2;
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int n;
    cin >> n;

    vector<int> xs(n);
    for (auto &x : xs) cin >> x;

    ll t{1};
    for (const auto h : xs) {
        t += turns_to_take_down(t, h);
    }
    cout << (t - 1) << '\n';
    return 0;
}
