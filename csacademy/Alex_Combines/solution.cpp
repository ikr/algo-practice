#include <bits/stdc++.h>
using namespace std;

template <typename T> ostream &operator<<(ostream &os, const vector<T> &xs) {
    os << '[';
    for (auto i = xs.cbegin(); i != xs.cend(); ++i) {
        if (i != xs.cbegin()) os << ' ';
        os << *i;
    }
    os << ']';
    return os;
}

using vi = vector<int>;
using pii = pair<int, int>;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

map<int, vi> indices_by_value(const vi &xs) {
    map<int, vi> ans;
    for (int i = 0; i < sz(xs); ++i) ans[xs[i]].push_back(i);
    return ans;
}

vi spans(const vi &xs, const map<int, vi> &ibv) {
    vi ans(sz(xs));
    ans.back() = sz(xs) - 1;

    for (int i = sz(xs) - 2; i >= 0; --i) {
        const int x = xs[i];
        assert(ibv.count(x));
        const auto &indices = ibv.at(x);

        const auto it = upper_bound(cbegin(indices), cend(indices), i);
        ans[i] = it == cend(indices) ? ans[i + 1] : min(*it - 1, ans[i + 1]);
    }

    return ans;
}

vi query_results(const vi &xs, const vector<pii> &queries) {
    const auto ss = spans(xs, indices_by_value(xs));
    cerr << ss << endl;

    vi ans;
    ans.reserve(sz(queries));
    return ans;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int n;
    cin >> n;

    vi xs(n);
    for (auto &x : xs) cin >> x;

    int q;
    cin >> q;
    vector<pii> queries(q);
    for (auto &[l, r] : queries) {
        cin >> l >> r;
        --l;
        --r;
    }

    const auto ans = query_results(xs, queries);
    for (const auto x : ans) cout << x << '\n';
    return 0;
}
