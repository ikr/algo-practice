#include <atcoder/lazysegtree.hpp>
#include <cassert>
#include <iostream>
using namespace std;

using ll = long long;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

constexpr ll op(const ll x, const ll y) { return x + y; }
constexpr ll e() { return 0LL; }

struct S final {
    ll value;
    ll size;
};

S S_op(S a, S b) { return {a.value + b.value, a.size + b.size}; }
S S_e() { return {0, 1}; }

S mapping(const ll f, const S x) { return {x.value + x.size * f, x.size}; }

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int N, M, Q;
    cin >> N >> M >> Q;

    atcoder::lazy_segtree<S, S_op, S_e, ll, mapping, op, e> cols(M + 1);
    vector<ll> rows(N, 0);

    for (int k = 1; k <= Q; ++k) {
        int cmd;
        cin >> cmd;

        if (cmd == 1) {
            int l, r, x;
            cin >> l >> r >> x;
            l--;
            r--;
            cols.apply(l, r + 1, x);
        } else if (cmd == 2) {
            int i, x;
            cin >> i >> x;
            --i;
            rows[i] = x;
        } else {
            assert(cmd == 3);
            int i, j;
            cin >> i >> j;
            --i;
            --j;

            const auto ans = rows[i] + cols.get(j).value;
            cout << ans << '\n';
        }
    }

    return 0;
}
