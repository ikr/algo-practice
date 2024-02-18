#include <bits/stdc++.h>
using namespace std;

using ll = long long;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

// https://github.com/kth-competitive-programming/kactl/blob/main/content/data-structures/SegmentTree.h
namespace kactl {
struct Tree {
    typedef ll T;
    static constexpr T unit = 1;
    T f(T a, T b) { return (a * b) % m; } // (any associative fn)
    Tree(ll m_, int n_ = 0, T def = unit) : m(m_), s(2 * n_, def), n(n_) {}
    void update(int pos, T val) {
        for (s[pos += n] = val; pos /= 2;)
            s[pos] = f(s[pos * 2], s[pos * 2 + 1]);
    }
    T query(int b, int e) { // query [b, e)
        T ra = unit, rb = unit;
        for (b += n, e += n; b < e; b /= 2, e /= 2) {
            if (b % 2) ra = f(ra, s[b++]);
            if (e % 2) rb = f(s[--e], rb);
        }
        return f(ra, rb);
    }
    vector<T> s;
    int n;
    ll m;
};
} // namespace kactl

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t;
    cin >> t;
    while (t--) {
        int n;
        ll m;
        cin >> n >> m;

        vector<ll> xs(n);
        for (auto &x : xs) cin >> x;

        kactl::Tree tree(m, n);
        for (int i = 0; i < n; ++i) {
            tree.update(i, xs[i]);
        }

        string cmd;
        cin >> cmd;
        assert(sz(cmd) == n);

        int a = 0;
        int b = n;
        for (const auto c : cmd) {
            cout << tree.query(a, b) << ' ';
            if (c == 'L') {
                ++a;
            } else {
                assert(c == 'R');
                --b;
            }
        }
        cout << '\n';
    }

    return 0;
}
