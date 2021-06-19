#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using pii = pair<int, int>;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}
template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

template <typename T1, typename T2>
ostream &operator<<(ostream &os, const pair<T1, T2> &x) {
    os << x.first << ' ' << x.second;
    return os;
}

ll manhattan(const pii p1, const pii p2) {
    return abs(p1.first - p2.first) + abs(p1.second - p2.second);
}

pair<pii, pii> place_yoyos(const int H, const int W, const pii p0) {
    const pii lt{1, 1};
    const pii rt{1, W};
    const pii rb{H, W};
    const pii lb{H, 1};

    const auto o1 = manhattan(p0, lt) + manhattan(lt, rb) + manhattan(rb, p0);
    const auto o2 = manhattan(p0, rt) + manhattan(rt, lb) + manhattan(lb, p0);

    return o1 > o2 ? pair{lt, rb} : pair{rt, lb};
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t;
    cin >> t;
    while (t--) {
        int H, W, ro0, co0;
        cin >> H >> W >> ro0 >> co0;

        const auto [p1, p2] = place_yoyos(H, W, {ro0, co0});
        cout << p1 << ' ' << p2 << '\n';
    }

    return 0;
}
