#include <atcoder/segtree>
#include <bits/stdc++.h>
using namespace std;

using ll = long long;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

ll op(ll a, ll b) { return min(a, b); }

ll e() { return LONG_LONG_MAX; }

vector<ll> min_sums_by_replacements_num(const ll T, const vector<ll> &xs) {
    vector<ll> ss(sz(xs));
    partial_sum(cbegin(xs), cend(xs), begin(ss));
    vector<ll> dp(sz(xs) + 1, ss.back());

    for (int k = 1; k <= sz(xs); ++k) {
        dp[k] = k * T + (ss.back() - ss[k - 1]);
    }

    return dp;
}

vector<ll> reversed(vector<ll> xs) {
    reverse(begin(xs), end(xs));
    return xs;
}

ll min_post_ops_sum(const ll L, const ll R, const vector<ll> &A) {
    const auto &xs = A;
    const auto ys = reversed(A);

    vector<ll> ss(sz(xs));
    partial_sum(cbegin(xs), cend(xs), begin(ss));

    const auto dpy = min_sums_by_replacements_num(R, ys);
    atcoder::segtree<ll, op, e> ty(dpy);

    ll result = accumulate(cbegin(A), cend(A), 0LL);
    for (int k = 0; k <= sz(A); ++k) {
        result = min(result, L * k - (k ? ss[k - 1] : 0LL) +
                                 ty.prod(0, sz(xs) - k + 1));
    }
    return result;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int N, L, R;
    cin >> N >> L >> R;

    vector<ll> A(N);
    for (auto &a : A) cin >> a;

    cout << min_post_ops_sum(L, R, A) << '\n';
    return 0;
}
