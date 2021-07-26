#include <bits/stdc++.h>
using namespace std;

using pii = pair<int, int>;

template <typename T1, typename T2>
ostream &operator<<(ostream &os, const pair<T1, T2> &x) {
    os << x.first << ' ' << x.second;
    return os;
}

pair<pii, pii> place_yoyos(const int H, const int W) {
    const pii lt{1, 1};
    const pii rb{H, W};
    return {lt, rb};
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t;
    cin >> t;
    while (t--) {
        int H, W, ro0, co0;
        cin >> H >> W >> ro0 >> co0;

        const auto [p1, p2] = place_yoyos(H, W);
        cout << p1 << ' ' << p2 << '\n';
    }

    return 0;
}
