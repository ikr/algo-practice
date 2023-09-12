#include <atcoder/segtree>
#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vi = vector<int>;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

constexpr ll op(ll a, ll b) { return max(a, b); }
constexpr ll e() { return 0; }

ll max_remaining_beauties_sum(const vi &h, const vi &a) {
    atcoder::segtree<ll, op, e> dp(sz(h) + 1);

    for (int i = 0; i < sz(h); ++i) {
        dp.set(h[i], a[i] + dp.prod(0, h[i]));
    }

    return dp.all_prod();
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int n;
    cin >> n;

    vi h(n);
    for (auto &x : h) cin >> x;

    vi a(n);
    for (auto &x : a) cin >> x;

    cout << max_remaining_beauties_sum(h, a) << '\n';
    return 0;
}
