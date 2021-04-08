#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using pii = pair<int, int>;
using vll = vector<ll>;
using vvll = vector<vll>;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}
template <typename T> constexpr ll llof(const T x) {
    return static_cast<ll>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

static constexpr ll M = 998244353LL;

int last_index_of_x_dividing_right_neigh(const vector<pii> &xys) {
    for (int i = 0; i < sz(xys) - 1; ++i) {
        const int x0 = xys[i].first;
        const int x1 = xys[i + 1].first;
        if (x1 % x0 != 0) return i - 1;
    }

    return sz(xys) - 2;
}

int divisions_num(const vector<pii> &xys) {
    const int hi = last_index_of_x_dividing_right_neigh(xys);
    if (hi < 0) return 0;

    if (!all_of(cbegin(xys) + hi + 2, cend(xys),
                [hi](const pii xy) { return xy.first % hi == 0; })) {
        return 0;
    }

    return -1;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    cout << setprecision(9) << fixed;

    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;

        vector<pii> xys(n);
        for (auto &[x, y] : xys) cin >> x >> y;

        sort(begin(xys), end(xys));
        cout << divisions_num(xys) << '\n';
    }

    return 0;
}
