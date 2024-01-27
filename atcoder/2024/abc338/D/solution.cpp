#include <atcoder/lazysegtree>
#include <bits/stdc++.h>
using namespace std;

using ll = long long;

using S = int;
using F = int;

constexpr S Inf = 1'000'000'000;

constexpr S op(const S a, const S b) { return std::min(a, b); }
constexpr S e() { return Inf; }
constexpr S mapping(const F f, const S x) { return f + x; }
constexpr F composition(const F f, const F g) { return f + g; }
constexpr F id() { return 0; }

constexpr int d_nat(const int a, const int b) { return abs(a - b); }
constexpr int d_mod(const int N, const int a, const int b) {
    assert(a < b);
    return a + N - b;
}

constexpr int d_with_bridge_k_removed(const int N, const int k, const int a,
                                      const int b) {
    assert(a < b);
    return (a <= k && k < b) ? d_mod(N, a, b) : d_nat(a, b);
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int N, M;
    cin >> N >> M;

    vector<int> X(M);
    for (auto &x : X) {
        cin >> x;
        --x;
    }

    vector<S> v(N, 0);
    atcoder::lazy_segtree<S, op, e, F, mapping, composition, id> seg(v);

    for (int i = 0; i < M - 1; ++i) {
        int a = X[i];
        int b = X[i + 1];
        if (a > b) swap(a, b);

        if (d_nat(a, b) < d_mod(N, a, b)) {
            seg.apply(a, b, 2);
        } else if (d_nat(a, b) > d_mod(N, a, b)) {
            seg.apply(0, a, 2);
            seg.apply(b, N, 2);
        } else {
            assert(d_nat(a, b) == d_mod(N, a, b));
            seg.apply(a, b, 1);
            seg.apply(0, a, 1);
            seg.apply(b, N, 1);
        }
    }

    ll ans = LONG_LONG_MAX;

    const auto lo = seg.all_prod();
    for (int k = 0; k < N; ++k) {
        if (seg.get(k) == lo) {
            ll candidate{};

            for (int i = 0; i < M - 1; ++i) {
                int a = X[i];
                int b = X[i + 1];
                if (a > b) swap(a, b);
                candidate += d_with_bridge_k_removed(N, k, a, b);
            }

            ans = min(ans, candidate);
        }
    }

    cout << ans << '\n';
    return 0;
}
