#include <atcoder/segtree>
#include <bits/stdc++.h>
using namespace std;

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
    map<int, int> fq;
    for (auto &a : A) {
        cin >> a;
        ++fq[a];
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
            const auto it = fq.find(old);
            assert(it != cend(fq));
            if (it->second == 1) {
                fq.erase(it);
            } else {
                fq[old] = it->second - 1;
            }

            seg.set(p, x);
            ++fq[x];
        } else {
            assert(op == 2);
            int l, r;
            cin >> l >> r;
            --l;
            --r;

            const auto hi = seg.prod(l, r + 1);
            const auto it = fq.lower_bound(hi);
            if (it == cbegin(fq)) {
                cout << 0 << '\n';
            } else {
                cout << prev(it)->second << '\n';
            }
        }
    }

    return 0;
}
