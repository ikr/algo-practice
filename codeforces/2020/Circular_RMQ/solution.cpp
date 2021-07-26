#include <bits/stdc++.h>
using namespace std;
using ll = long long;

namespace atcoder {
namespace internal {
int ceil_pow2(int n) {
    int x = 0;
    while ((1U << x) < static_cast<unsigned int>(n)) x++;
    return x;
}
} // namespace internal

template <class S, S (*op)(S, S), S (*e)(), class F, S (*mapping)(F, S),
          F (*composition)(F, F), F (*id)()>
struct lazy_segtree final {
    lazy_segtree() : lazy_segtree(0) {}
    lazy_segtree(int n) : lazy_segtree(vector<S>(n, e())) {}
    lazy_segtree(const vector<S> &v) : _n(int(v.size())) {
        log = internal::ceil_pow2(_n);
        size = 1 << log;
        d = vector<S>(2 * size, e());
        lz = vector<F>(size, id());
        for (int i = 0; i < _n; i++) d[size + i] = v[i];
        for (int i = size - 1; i >= 1; i--) {
            update(i);
        }
    }

    void set(int p, S x) {
        assert(0 <= p && p < _n);
        p += size;
        for (int i = log; i >= 1; i--) push(p >> i);
        d[p] = x;
        for (int i = 1; i <= log; i++) update(p >> i);
    }

    S get(int p) {
        assert(0 <= p && p < _n);
        p += size;
        for (int i = log; i >= 1; i--) push(p >> i);
        return d[p];
    }

    S prod(int l, int r) {
        assert(0 <= l && l <= r && r <= _n);
        if (l == r) return e();

        l += size;
        r += size;

        for (int i = log; i >= 1; i--) {
            if (((l >> i) << i) != l) push(l >> i);
            if (((r >> i) << i) != r) push(r >> i);
        }

        S sml = e(), smr = e();
        while (l < r) {
            if (l & 1) sml = op(sml, d[l++]);
            if (r & 1) smr = op(d[--r], smr);
            l >>= 1;
            r >>= 1;
        }

        return op(sml, smr);
    }

    S all_prod() { return d[1]; }

    void apply(int p, F f) {
        assert(0 <= p && p < _n);
        p += size;
        for (int i = log; i >= 1; i--) push(p >> i);
        d[p] = mapping(f, d[p]);
        for (int i = 1; i <= log; i++) update(p >> i);
    }
    void apply(int l, int r, F f) {
        assert(0 <= l && l <= r && r <= _n);
        if (l == r) return;

        l += size;
        r += size;

        for (int i = log; i >= 1; i--) {
            if (((l >> i) << i) != l) push(l >> i);
            if (((r >> i) << i) != r) push((r - 1) >> i);
        }

        {
            int l2 = l, r2 = r;
            while (l < r) {
                if (l & 1) all_apply(l++, f);
                if (r & 1) all_apply(--r, f);
                l >>= 1;
                r >>= 1;
            }
            l = l2;
            r = r2;
        }

        for (int i = 1; i <= log; i++) {
            if (((l >> i) << i) != l) update(l >> i);
            if (((r >> i) << i) != r) update((r - 1) >> i);
        }
    }

  private:
    int _n, size, log;
    vector<S> d;
    vector<F> lz;

    void update(int k) { d[k] = op(d[2 * k], d[2 * k + 1]); }
    void all_apply(int k, F f) {
        d[k] = mapping(f, d[k]);
        if (k < size) lz[k] = composition(f, lz[k]);
    }
    void push(int k) {
        all_apply(2 * k, lz[k]);
        all_apply(2 * k + 1, lz[k]);
        lz[k] = id();
    }
};
} // namespace atcoder

constexpr ll e() { return 1e18; }
constexpr ll z() { return 0; }
constexpr ll mmin(const ll x, const ll y) { return min(x, y); }
constexpr ll mplus(const ll x, const ll y) { return x + y; }

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n;
    cin >> n;
    vector<ll> xs(n, 0);
    for (auto &x : xs) cin >> x;

    atcoder::lazy_segtree<ll, mmin, e, ll, mplus, mplus, z> tree(xs);
    int ops;
    cin >> ops;
    cin >> ws;
    while (ops--) {
        string line;
        getline(cin, line);

        const int spaces_count = count(cbegin(line), cend(line), ' ');
        stringstream ss(line);
        if (spaces_count == 1) {
            int lf, rg;
            ss >> lf >> rg;

            if (lf <= rg) {
                cout << tree.prod(lf, rg + 1) << '\n';
            } else {
                cout << min(tree.prod(0, rg + 1), tree.prod(lf, n)) << '\n';
            }
        } else {
            int lf, rg, v;
            ss >> lf >> rg >> v;

            if (lf <= rg) {
                tree.apply(lf, rg + 1, v);
            } else {
                tree.apply(0, rg + 1, v);
                tree.apply(lf, n, v);
            }
        }
    }

    return 0;
}
