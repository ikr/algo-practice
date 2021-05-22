#include <bits/stdc++.h>
using namespace std;

using vi = vector<int>;
using vvi = vector<vi>;
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

constexpr int mlog2(const unsigned int x) {
    return inof(8U * sizeof(unsigned int) - __builtin_clz(x) - 1U);
}

vvi jumps(const vi &ss) {
    const int n = sz(ss);
    vvi ans(n, vi(mlog2(n) + 1, -1));

    for (int i = 0; i < n; ++i) ans[i][0] = ss[i] + 1;

    for (int j = 1; j <= mlog2(n); ++j) {
        for (int i = 0; i < n; ++i) {
            ans[i][j] = ans[i][j - 1] == n ? n : ans[ans[i][j - 1]][j - 1];
        }
    }

    return ans;
}

int groups_num(const vvi &js, int l, const int r) {
    assert(l <= r);
    const int n = sz(js);

    int ans = 1;

    while (js[l][0] <= r) {
        int e = 0;
        assert(l < n);
        while (js[l][e + 1] < r) ++e;

        l = js[l][e];
        ans += (1 << e);
    }

    return ans;
}

vi query_results(const vi &xs, const vector<pii> &queries) {
    const auto ss = spans(xs, indices_by_value(xs));
    const auto js = jumps(ss);

    vi ans;
    ans.reserve(sz(queries));

    for (const auto [l, r] : queries) {
        ans.push_back(groups_num(js, l, r));
    }

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
