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

ll opt_diff(vector<ll> A, const ll K) {
    const auto T = A.back();
    for (int i = 0; i < sz(A); ++i) {
        const ll q = (T - A[i]) / K;
        const auto a = A[i] + q * K;
        A[i] = a;
    }
    sort(begin(A), end(A));

    atcoder::segtree<ll, lo_op, lo_e> t_lo(A);
    atcoder::segtree<ll, hi_op, hi_e> t_hi(A);
    ll result = t_hi.all_prod() - t_lo.all_prod();
    for (int i = 0; i < sz(A); ++i) {
        t_lo.set(i, A[i] + K);
        t_hi.set(i, A[i] + K);
        const ll result_ = t_hi.all_prod() - t_lo.all_prod();

        if (result_ < result) {
            result = result_;
        } else {
            break;
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
        cout << opt_diff(std::move(A), K) << '\n';
    }

    return 0;
}
