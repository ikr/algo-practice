#include <atcoder/segtree>
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace std;
using namespace __gnu_pbds;

template <typename T>
using ordered_set =
    tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

int op(int a, int b) { return max(a, b); }

int e() { return 0; }

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int N, Q;
    cin >> N >> Q;

    vector<int> A(N);
    for (auto &a : A) {
        cin >> a;
    }

    map<int, ordered_set<int>> idx;
    for (int i = 0; i < N; ++i) {
        idx[A[i]].insert(i);
    }

    atcoder::segtree<int, op, e> seg(A);

    for (int q = 1; q <= Q; ++q) {
        int op;
        cin >> op;

        if (op == 1) {
            int p, x;
            cin >> p >> x;
            --p;

            const auto old = seg.get(p);
            assert(idx.contains(old));
            if (sz(idx[old]) == 1) {
                idx.erase(old);
            } else {
                idx[old].erase(p);
            }
            seg.set(p, x);
            idx[x].insert(p);
        } else {
            assert(op == 2);
            int l, r;
            cin >> l >> r;
            --l;
            --r;

            const auto hi = seg.prod(l, r + 1);

            auto it = idx.lower_bound(hi);
            if (it == cbegin(idx)) {
                cout << 0 << '\n';
            } else {
                const auto a = prev(it)->first;
                const auto y = sz(idx[a]) - idx[a].order_of_key(l);
                cout << y << '\n';
            }
        }
    }

    return 0;
}
