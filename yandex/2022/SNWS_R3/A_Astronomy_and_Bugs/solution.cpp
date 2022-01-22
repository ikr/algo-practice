#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using pii = pair<int, int>;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

ll max_distortions(const vector<pii> &xys) {
    set<int> xs;
    map<int, int> xf;
    set<int> ys;
    map<int, int> yf;

    for (const auto [x, y] : xys) {
        xs.insert(x);
        ++xf[x];
        ys.insert(y);
        ++yf[y];
    }

    ll ans = 1LL * sz(xs) * sz(ys);
    for (const auto [x, y] : xys) {
        if (xf[x] == 1 && yf[y] == 1) {
            --ans;
        }
    }
    return ans;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int n;
    cin >> n;

    vector<pii> xys(n);
    for (auto &[x, y] : xys) cin >> x >> y;

    cout << max_distortions(xys) << '\n';
    return 0;
}
