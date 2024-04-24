#include <atcoder/segtree>
#include <bits/stdc++.h>
using namespace std;

using ll = long long;

ll lo_op(ll a, ll b) { return min(a, b); }
ll lo_e() { return (ll)(1e9); }
ll hi_op(ll a, ll b) { return max(a, b); }
ll hi_e() { return 0; }

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

ll opt_diff(const vector<ll> &A, const ll K) {
    const auto T = A.back();
    atcoder::segtree<ll, lo_op, lo_e> t_lo(A);
    atcoder::segtree<ll, hi_op, hi_e> t_hi(A);

    ll result = t_hi.all_prod() - t_lo.all_prod();
    for (int i = 0; i < sz(A); ++i) {
        const ll q = (T - A[i]) / K;
        const auto one = A[i] + q * K;
        const auto two = A[i] + (q + 1) * K;

        for (const auto a : {one, two}) {
            t_lo.set(i, a);
            t_hi.set(i, a);
            result = min(result, t_hi.all_prod() - t_lo.all_prod());
        }
    }
    return result;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t;
    cin >> t;
    while (t--) {
        int N, K;
        cin >> N >> K;

        vector<ll> A(N);
        for (auto &a : A) cin >> a;
        sort(begin(A), end(A));
        cout << opt_diff(A, K) << '\n';
    }

    return 0;
}
