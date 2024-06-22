#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int tile_part(const ll x, const ll y) {
    if (y % 2LL == 0) {
        return x % 2LL == 0 ? 0 : 1;
    }
    return x % 2LL == 1 ? 0 : 1;
}

ll min_toll(const ll x0, const ll y0, const ll x1, const ll y1) {
    const auto dx = abs(x0 - x1);
    const auto dy = abs(y0 - y1);

    if (dy >= dx) {
        return dx + (dy - dx);
    }

    auto a = min(x0, x1);
    if (tile_part(a, y1) == 1) --a;

    auto b = max(x0, x1);
    if (tile_part(b, y1) == 1) --b;

    return (b - a) / 2LL;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    ll a, b, c, d;
    cin >> a >> b >> c >> d;
    cout << min_toll(a, b, c, d) << '\n';
    return 0;
}
