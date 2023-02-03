#include <bits/stdc++.h>
using namespace std;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

// https://github.com/kth-competitive-programming/kactl/blob/main/content/data-structures/LazySegmentTree.h
namespace kactl {
static constexpr int inf = 1e9;
using vi = vector<int>;
struct Node {
    Node *l = 0, *r = 0;
    int lo, hi, mset = inf, madd = 0, val = -inf;
    Node(int lo, int hi) : lo(lo), hi(hi) {} // Large interval of -inf
    Node(vi &v, int lo, int hi) : lo(lo), hi(hi) {
        if (lo + 1 < hi) {
            int mid = lo + (hi - lo) / 2;
            l = new Node(v, lo, mid);
            r = new Node(v, mid, hi);
            val = max(l->val, r->val);
        } else
            val = v[lo];
    }
    int query(int L, int R) {
        if (R <= lo || hi <= L) return -inf;
        if (L <= lo && hi <= R) return val;
        push();
        return max(l->query(L, R), r->query(L, R));
    }
    void set(int L, int R, int x) {
        if (R <= lo || hi <= L) return;
        if (L <= lo && hi <= R)
            mset = val = x, madd = 0;
        else {
            push(), l->set(L, R, x), r->set(L, R, x);
            val = max(l->val, r->val);
        }
    }
    void add(int L, int R, int x) {
        if (R <= lo || hi <= L) return;
        if (L <= lo && hi <= R) {
            if (mset != inf)
                mset += x;
            else
                madd += x;
            val += x;
        } else {
            push(), l->add(L, R, x), r->add(L, R, x);
            val = max(l->val, r->val);
        }
    }
    void push() {
        if (!l) {
            int mid = lo + (hi - lo) / 2;
            l = new Node(lo, mid);
            r = new Node(mid, hi);
        }
        if (mset != inf)
            l->set(lo, hi, mset), r->set(lo, hi, mset), mset = inf;
        else if (madd)
            l->add(lo, hi, madd), r->add(lo, hi, madd), madd = 0;
    }
};
} // namespace kactl

int apply_op(int n) {
    int ans{};
    while (n) {
        ans += (n % 10);
        n /= 10;
    }

    return ans;
}

int apply_k_ops(int k, int x) {
    for (; k > 0; --k) {
        const auto x_ = apply_op(x);
        if (x_ == x) break;
        x = x_;
    }
    return x;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t;
    cin >> t;
    while (t--) {
        int n, q;
        cin >> n >> q;

        vector<int> xs(n);
        for (auto &x : xs) cin >> x;

        vector<int> ops(n, 0);
        kactl::Node *tr = new kactl::Node(ops, 0, sz(ops));

        for (int k = 0; k < q; ++k) {
            int cmd;
            cin >> cmd;

            if (cmd == 1) {
                int l, r;
                cin >> l >> r;
                --l;
                tr->add(l, r, 1);
            } else {
                assert(cmd == 2);
                int ii;
                cin >> ii;
                --ii;
                const auto ans = apply_k_ops(tr->query(ii, ii + 1), xs[ii]);
                cout << ans << '\n';
            }
        }

        delete tr;
    }

    return 0;
}
