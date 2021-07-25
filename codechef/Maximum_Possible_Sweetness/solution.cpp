#include <atcoder/segtree>
#include <bits/stdc++.h>
using namespace std;

using vi = vector<int>;
using pii = pair<int, int>;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

pair<vi, vi> reorder_by_p(const vi &p, const vi &s) {
    const int n = sz(p);
    vector<pii> xs(n);

    for (int i = 0; i < n; ++i) {
        xs[i] = pii{p[i], -s[i]};
    }

    sort(begin(xs), end(xs));

    vi p_(n);
    vi s_(n);
    for (int i = 0; i < n; ++i) {
        p_[i] = xs[i].first;
        s_[i] = -xs[i].second;
    }
    return {p_, s_};
}

int op(const int a, const int b) { return max(a, b); }
int e() { return 0; }

int bounding_index(const vi &xs, const int hi) {
    const auto it = upper_bound(cbegin(xs), cend(xs), hi);
    return inof(distance(cbegin(xs), it));
}

int max_sweetness(const int d, const vi &p, const vi &s) {
    const int n = sz(p);
    const atcoder::segtree<int, op, e> t(s);

    int ans = 0;

    for (int i = 0; i < n; ++i) {
        if (p[i] >= d) continue;
        ans = max(ans, s[i]);

        const auto j = bounding_index(p, d - p[i]);
        if (j <= i) {
            ans = max(ans, s[i] + t.prod(0, j));
        } else {
            ans = max(ans, s[i] + t.prod(0, i));
            ans = max(ans, s[i] + t.prod(i + 1, j));
        }
    }

    return ans;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t;
    cin >> t;
    while (t--) {
        int n, d;
        cin >> n >> d;

        vi p(n, 0);
        for (auto &x : p) cin >> x;

        vi s(n, 0);
        for (auto &x : s) cin >> x;

        const auto in = reorder_by_p(p, s);
        cout << max_sweetness(d, in.first, in.second) << '\n';
    }

    return 0;
}
