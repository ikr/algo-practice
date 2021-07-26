#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vi = vector<int>;
using vvi = vector<vi>;
using pii = pair<int, int>;
using vll = vector<ll>;
using vvll = vector<vll>;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}
template <typename T> constexpr ll llof(const T x) {
    return static_cast<ll>(x);
}
template <typename T> constexpr double doof(const T x) {
    return static_cast<double>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    cout << setprecision(9) << fixed;

    int n;
    cin >> n;

    vi xs(n);
    for (auto &x : xs) cin >> x;

    vi ys(n);
    for (auto &y : ys) cin >> y;

    int lo = 0;
    int hi = 1e9;

    for (int i = 0; i < sz(xs); ++i) {
        lo = max(lo, xs[i]);
        hi = min(hi, ys[i]);
    }

    const int ans = lo <= hi ? hi - lo + 1 : 0;
    cout << ans << '\n';
    return 0;
}
